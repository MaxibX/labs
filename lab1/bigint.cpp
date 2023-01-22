#include"bigint.h"

using namespace std;

namespace BigInt {
    BigInt::BigInt() {
        sign = PLUS;
        digits.push_back(0);
    }
    BigInt::BigInt(int number) {
        if (number >= 0) sign = PLUS;
        else {
            sign = MINUS;
            number = abs(number);
        }
        do {
            digits.push_back(number % INTMAX);
            number /= INTMAX;
        } while (number);
        (*this).is_minus_zero();
    }

    BigInt::BigInt(string str) {
        int str_len = str.size();
        for (int i = 0; i < str_len; ++i) {
            if (i != 0)
                if (!isdigit(str[i])) throw invalid_argument("NaN\n");
                else if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-') throw invalid_argument("NaN\n");
        }
        int digits_len = 0, count = 1, rank = 1;
        digits.push_back(0);
        if (str[0] == '-') {
            sign = MINUS;
            str.erase(0,1);
        }
        else {
            sign = PLUS;
            if (str[0] == '+') {
                str.erase(0,1);
            }
        }
        for (int i = str.size() - 1; i >= 0; --i) {
            if (count > BASE) {
                digits.push_back(0);
                digits_len++;
                count = 1;
                rank = 1;
            }
            digits[digits_len] += (str[i] - '0') * rank;
            count++;
            rank *= 10;
        }
        (*this).is_minus_zero();
    }
    BigInt::BigInt(const BigInt &second) {
        this->digits = second.digits;
        this->sign = second.sign;
    }
    BigInt::~BigInt() {
        this->digits.clear();
    }
    BigInt& BigInt::operator=(const BigInt &second) {
        this->sign = second.sign;
        this->digits = second.digits;
        return *this;
    }
    BigInt BigInt::operator~() const {
        BigInt result = *this;
        ++result;
        result.sign = (result.sign == MINUS) ? PLUS : MINUS;
        result.is_minus_zero();
        return result;
    }

    BigInt& BigInt::operator++() {
        return *this += 1;
    }
    const BigInt BigInt::operator++(int) {
        BigInt temp = *this;
        *this += 1;
        return temp;
    }
    BigInt& BigInt::operator--() {
        return *this -= 1;
    }
    const BigInt BigInt::operator--(int) {
        BigInt temp = *this;
        *this -= 1;
        return temp;
    }
    BigInt& BigInt::operator+=(const BigInt &second) {
        int rank = 0;
        BigInt min_num, max_num;
        if (this->digits == max_number(this->digits, second.digits)) {
            min_num = second;
            max_num = *this;
        }
        else {
            min_num = *this;
            max_num = second;
        }
        int digit_min_len = min((int) this->digits.size(), (int) second.digits.size());
        int idx = digit_min_len;
        if (this->sign == second.sign) {
            for (int i = 0; i < digit_min_len; ++i) {
                max_num.digits[i] += min_num.digits[i] + rank;
                rank = max_num.digits[i] / INTMAX;
                max_num.digits[i] %= INTMAX;
            }
            if (rank && max_num.digits.size() != min_num.digits.size()) {
                do {
                    max_num.digits[idx] += rank;
                    rank = max_num.digits[idx] / INTMAX;
                    max_num.digits[idx] %= INTMAX;
                    idx++;
                } while (idx < max_num.digits.size() && rank);
                if (idx == max_num.digits.size() - 1 && rank) max_num.digits.push_back(rank);
            }
            else if (rank && max_num.digits.size() == min_num.digits.size()) max_num.digits.push_back(rank);
        }
        else {
            if (this->digits.size() != 1) {
                for (int i = 0; i < digit_min_len; ++i) {
                    max_num.digits[i] += INTMAX - min_num.digits[i] - rank;
                    if (max_num.digits[i] < INTMAX) rank = 1;
                    else {
                        max_num.digits[i] %= INTMAX;
                        rank = 0;
                    }
                }
                if (rank == 1) {
                    do {
                        max_num.digits[idx] += INTMAX - rank;
                        if (max_num.digits[idx] < INTMAX) rank = 1;
                        else {
                            max_num.digits[idx] %= INTMAX;
                            rank = 0;
                        }
                        idx++;
                    } while (idx < max_num.digits.size() && rank);
                }
            }
            else max_num.digits[0] = abs(max_num.digits[0] - min_num.digits[0]);
        }
        this->digits = max_num.digits;
        this->sign = max_num.sign;
        (*this).remove_first_zeros();
        (*this).is_minus_zero();
        return *this;
    }
    BigInt& BigInt::operator-=(const BigInt &second) {
        return *this += (-second);
    }
    BigInt& BigInt::operator*=(const BigInt &second) {
        long long int rank, number_temp;
        BigInt min_num, max_num, temp, result;
        if (this->digits == max_number(this->digits, second.digits)) {
            min_num = second;
            max_num = *this;
        }
        else {
            max_num = second;
            min_num = *this;
        }
        string min_num_str = string(min_num);
        if (min_num_str[0] == '-' || min_num_str[0] == '+') min_num_str.erase(0,1);
        int min_num_str_len = min_num_str.size();
        int zero_addit = min_num_str_len;
        int max_num_len = max_num.digits.size();
        for (int i = 0; i < min_num_str_len; ++i) {
            temp = max_num;
            long long int number = (int)(min_num_str[i] - '0');
            rank = 0;
            for (int j = 0; j < max_num_len; ++j) {
                number_temp = (long long int)(temp.digits[j]);
                number_temp = number_temp * number + rank;
                rank = (int)(number_temp / INTMAX);
                temp.digits[j] = (int)(number_temp % INTMAX);
            }
            if (rank) temp.digits.push_back(rank);
            string temp_str = string(temp);
            for (int zero = 0; zero < zero_addit - 1; ++zero) temp_str += '0';
            temp = BigInt(temp_str);
            result += temp;
            zero_addit--;
        }
        this->digits = result.digits;
        if (this->sign == second.sign) this->sign = PLUS;
        else this->sign = MINUS;
        (*this).is_minus_zero();
        return *this;
    }
    BigInt& BigInt::operator/=(const BigInt &second) {
        if (second == BigInt(0)) throw invalid_argument("division by zero\n");
        BigInt temp, result, number = second;
        number.sign = PLUS;
        result.digits.resize(this->digits.size());
        bool this_sign = this->sign;
        for (int i = this->digits.size() - 1; i >= 0; --i) {
            temp.shift_right();
            temp.digits[0] = this->digits[i];
            temp.remove_first_zeros();
            int l = 0, r = INTMAX, factor = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                BigInt sel_temp = BigInt(mid) * number;
                if (sel_temp <= temp) {
                    factor = mid;
                    l = mid + 1;
                }
                else r = mid - 1;
            }
            result.digits[i] = factor;
            temp -= BigInt(factor) * number;
        }
        result.remove_first_zeros();
        *this = result;
        if (this_sign == second.sign) this->sign = PLUS;
        else this->sign = MINUS;
        (*this).is_minus_zero();
        return *this;
    }
    BigInt& BigInt::operator^=(const BigInt &second) {
        BigInt result;
        string min_str, max_str = get_max_str(second);
        if (max_str == (*this).BigInt_to_binary()) min_str = second.BigInt_to_binary();
        else min_str = (*this).BigInt_to_binary();
        int min_idx = (int) min_str.size() - 1, max_idx = (int) max_str.size() - 1;
        while (min_idx >= 0) {
            if (min_str[min_idx] == max_str[max_idx]) max_str[max_idx] = '0';
            else max_str[max_idx] = '1';
            --min_idx;
            --max_idx;
        }
        result.binary_to_BigInt(max_str);
        result.sign = (this->sign == second.sign) ? PLUS : MINUS;
        *this = result;
        (*this).is_minus_zero();
        return *this;
    }
    BigInt& BigInt::operator%=(const BigInt &second) {
        BigInt temp = second;
        temp.sign = PLUS;
        this->sign = PLUS;
        return *this -= (*this / temp) * temp;
    }
    BigInt& BigInt::operator&=(const BigInt &second) {
        BigInt result, temp = second;
        int this_sign = this->sign;
        vector<string> str_result = get_result_str(temp, this_sign, second.sign);
        string min_str = str_result[1];
        string max_str = str_result[0];
        int max_idx = max_str.size() - 1;
        while (max_idx >= 0) {
            if (max_str[max_idx] == '1' && min_str[max_idx] == '1') max_str[max_idx] = '1';
            else max_str[max_idx] = '0';
            --max_idx;
        }
        if (this_sign == MINUS && second.sign == MINUS) {
            max_str = invert(max_str);
            result.binary_to_BigInt(max_str);
            ++result;
            result.sign = MINUS;
        }
        else {
            result.binary_to_BigInt(max_str);
            result.sign = PLUS;
        }
        *this = result;
        (*this).is_minus_zero();
        return *this;
    }
    BigInt& BigInt::operator|=(const BigInt &second) {
        BigInt result, temp = second;
        int this_sign = this->sign;
        vector<string> str_result = get_result_str(temp, this_sign, second.sign);
        string min_str = str_result[1];
        string max_str = str_result[0];
        int max_idx = max_str.size() - 1;
        while (max_idx >= 0) {
            if (max_str[max_idx] == '0' && min_str[max_idx] == '0') max_str[max_idx] = '0';
            else max_str[max_idx] = '1';
            --max_idx;
        }
        if (this_sign == MINUS && second.sign == MINUS) {
            max_str = invert(max_str);
            result.binary_to_BigInt(max_str);
            result.sign = PLUS;
            ++result;
            result.sign = MINUS;
        }
        else {
            result.binary_to_BigInt(max_str);
        }
        *this = result;
        (*this).is_minus_zero();
        return *this;
    }
    BigInt BigInt::operator+() const {
        return *this;
    }
    BigInt BigInt::operator-() const {
        BigInt temp = *this;
        temp.sign = (temp.sign == PLUS) ? MINUS : PLUS;
        temp.is_minus_zero();
        return temp;
    }

    bool BigInt::operator==(const BigInt &second) const {
        if (this->digits == second.digits && this->sign == second.sign) return true;
        return false;
    }
    bool BigInt::operator!=(const BigInt &second) const {
        return !(*this == second);
    }
    bool BigInt::operator<(const BigInt &second) const {
        if (this->sign == second.sign) {
            if (this->digits == second.digits) return false;
            if (this->digits == max_number(this->digits, second.digits)) {
                if (this->sign == MINUS) return true;
                else return false;
            }
            if (second.digits == max_number(this->digits, second.digits)) {
                if (this->sign == MINUS) return false;
                else return true;
            }

        }
        else if (this->sign == MINUS) return true;
        return false;
    }
    bool BigInt::operator>(const BigInt &second) const {
        return !(*this < second || *this == second);
    }
    bool BigInt::operator<=(const BigInt &second) const {
        return *this < second || *this == second;
    }
    bool BigInt::operator>=(const BigInt &second) const {
        return *this > second || *this == second;
    }
    BigInt::operator int() const {
        if (this->digits.size() == 1) {
            int temp = (*this).digits[0];
            if (this->sign == MINUS) temp = -temp;
            return temp;
        }
        string str(*this);
        string str_temp;
        if (str[0] == '-') str.erase(0,1);
        str_temp.append(str, 0, BASE);
        int result = stoi(str_temp);
        return (this->sign == MINUS) ? -result : result;
    }
    BigInt::operator string() const {
        std::string str;
        if (this->sign == MINUS) str += "-";
        int digits_len = this->digits.size() - 1;
        for (int i = digits_len; i >= 0; --i) {
            int temp = this->digits[i], digits_count = 0, zeros_count;
            string str_temp;
            do {
                str_temp.insert(0, 1, (char) ('0' + temp % 10));
                temp /= 10;
                ++digits_count;
            } while (temp);
            zeros_count = BASE - digits_count;
            if (i != digits_len) {
                for (int j = 1; j <= zeros_count; ++j) str += "0";
            }
            str += str_temp;
        }
        return str;
    }
    size_t BigInt::size() const {
        return (*this).digits.size() * sizeof(int) + 2 * sizeof(int) + 3 * sizeof(bool);
    }


    vector<int> BigInt::max_number(vector<int> number1, vector<int> number2) const {
        if (number1 == number2 || number1.size() > number2.size()) {
            return number1;
        }
        else if (number1.size() < number2.size()) return number2;
        if (number1.size() == number2.size()) {
            int number_len = number1.size() - 1;
            for (int i = number_len; i >= 0; --i) {
                if (number1[i] < number2[i]) {
                    return number2;
                }
                else if (number1[i] > number2[i]) return number1;
            }
        }
        return number1;
    }
    void BigInt::shift_right() {
        this->digits.push_back(0);
        for (int i = this->digits.size() - 1; i > 0; --i) this->digits[i] = this->digits[i - 1];
    }
    void BigInt::remove_first_zeros() {
        int digits_i = this->digits.size() - 1;
        while (this->digits[digits_i] == 0 && digits_i > 0) {
            this->digits.pop_back();
            digits_i--;
        }
    }
    string BigInt::BigInt_to_binary() const {
        BigInt temp = *this, binary = 2;
        temp.sign = PLUS;
        string str_temp;
        while (temp != BigInt(0)) {
            str_temp.insert(0, 1, (char)((int)(temp % binary) + '0'));
            temp /= binary;
        }
        return str_temp;
    }
    void BigInt::binary_to_BigInt(string str) {
        BigInt result, binary_deg = 1, binary = 2;
        for (int i = str.size() - 1; i >= 0; --i) {
            int number = (int)(str[i] - '0');
            result += BigInt(number) * binary_deg;
            binary_deg *= binary;
        }
        *this = result;
    }
    void BigInt::is_minus_zero() {
        if (this->digits.size() == 1 && this->digits[0] == 0 && this->sign == MINUS) this->sign = PLUS;
    }
    string BigInt::invert(string str) {
        for (int i = str.size() - 1; i >= 0; --i) {
            if (str[i] == '0') str[i] = '1';
            else str[i] = '0';
        }
        return str;
    }
    string BigInt::get_max_str(const BigInt& second) const {
        string this_str = (*this).BigInt_to_binary();
        string second_str = second.BigInt_to_binary();
        string max_str;
        if (this_str.size() >= second_str.size()) max_str = this_str;
        else max_str = second_str;
        return max_str;
    }
    void BigInt::bit_neg_check() {
        if (this->sign == MINUS) {
            *this = ~*this;
        }
    }
    string BigInt::str_invert_check(string str, bool str_sign) {
        if (str_sign == MINUS) return invert(str);
        else return str;
    }
    vector<string> BigInt::get_result_str(BigInt &temp, int this_sign, int second_sign) {
        vector<string> result;
        (*this).bit_neg_check();
        temp.bit_neg_check();
        int min_str_sign, max_str_sign;
        string min_str, max_str = get_max_str(temp);
        if (max_str == (*this).BigInt_to_binary()) {
            min_str = temp.BigInt_to_binary();
            min_str_sign = second_sign;
            max_str_sign = this_sign;
        }
        else {
            min_str = (*this).BigInt_to_binary();
            min_str_sign = this_sign;
            max_str_sign = second_sign;
        }
        min_str.insert(0, max_str.size() - min_str.size(), '0');
        min_str = str_invert_check(min_str, min_str_sign);
        max_str = str_invert_check(max_str, max_str_sign);
        result.push_back(min_str);
        result.push_back(max_str);
        return result;
    }
    ostream &operator<<(ostream &o, const BigInt& i) {
        string res(i);
        o<<res;
        return o;
    }
    BigInt operator+(const BigInt& first, const BigInt& second) {
        BigInt temp = first;
        temp += second;
        return temp;
    }
    BigInt operator-(const BigInt& first, const BigInt& second) {
        BigInt temp = first;
        temp -= second;
        return temp;
    }
    BigInt operator*(const BigInt& first, const BigInt& second) {
        BigInt temp = first;
        temp *= second;
        return temp;
    }
    BigInt operator/(const BigInt& first, const BigInt& second) {
        BigInt temp = first;
        temp /= second;
        return temp;
    }
    BigInt operator^(const BigInt& first, const BigInt& second) {
        BigInt temp = first;
        temp ^= second;
        return temp;
    }
    BigInt operator%(const BigInt& first, const BigInt& second) {
        BigInt temp = first;
        temp %= second;
        return temp;
    }
    BigInt operator&(const BigInt& first, const BigInt& second) {
        BigInt temp = first;
        temp &= second;
        return temp;
    }
    BigInt operator|(const BigInt& first, const BigInt& second) {
        BigInt temp = first;
        temp |= second;
        return temp;
    }
}