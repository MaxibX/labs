#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include<iostream>
#include<vector>
#include<string>

using namespace std;

namespace BigInt {
    class BigInt {
    private:
        vector<int> digits;
        bool sign;
        const bool PLUS = false;
        const bool MINUS = true;
        int INTMAX = 1000000000;
        const int BASE = 9;

    public:
        BigInt();
        BigInt(int);
        BigInt(string);
        BigInt(const BigInt&);
        ~BigInt();

        BigInt& operator=(const BigInt&);

        BigInt operator~() const;

        BigInt& operator++();
        const BigInt operator++(int);
        BigInt& operator--();
        const BigInt operator--(int);

        BigInt& operator+=(const BigInt&);
        BigInt& operator*=(const BigInt&);
        BigInt& operator-=(const BigInt&);
        BigInt& operator/=(const BigInt&);
        BigInt& operator^=(const BigInt&);
        BigInt& operator%=(const BigInt&);
        BigInt& operator&=(const BigInt&);
        BigInt& operator|=(const BigInt&);

        BigInt operator+() const;
        BigInt operator-() const;

        bool operator==(const BigInt&) const;
        bool operator!=(const BigInt&) const;
        bool operator<(const BigInt&) const;
        bool operator>(const BigInt&) const;
        bool operator<=(const BigInt&) const;
        bool operator>=(const BigInt&) const;

        operator int() const;
        operator string() const;

        size_t size() const;

        void shift_right();

        void remove_first_zeros();

        string BigInt_to_binary() const;

        void binary_to_BigInt(string str);

        void is_minus_zero();

        string invert(string str);

        string get_max_str(const BigInt &second) const;

        void bit_neg_check();

        string str_invert_check(string str, bool str_sign);

        vector<string> get_result_str(BigInt &temp, int this_sign, int second_sign);

        vector<int> max_number(vector<int> number1, vector<int> number2) const;
    };
    BigInt operator+(const BigInt&, const BigInt&);
    BigInt operator-(const BigInt&, const BigInt&);
    BigInt operator*(const BigInt&, const BigInt&);
    BigInt operator/(const BigInt&, const BigInt&);
    BigInt operator^(const BigInt&, const BigInt&);
    BigInt operator%(const BigInt&, const BigInt&);
    BigInt operator&(const BigInt&, const BigInt&);
    BigInt operator|(const BigInt&, const BigInt&);

    ostream& operator<<(ostream& o, const BigInt& i);
}

#endif //LAB1_BIGINT_H
