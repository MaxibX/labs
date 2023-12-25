#include"universe.h"

using namespace std;

namespace game {
    universe::~universe() {
        this->coords.clear();
        this->gamerule_to_alive_count.clear();
        this->gamerule_to_survive_count.clear();
    }
    void universe::set_game_version(string temp) {
        if (!temp.empty() && temp == CURRENT_VERSION) {
            game_version = temp;
            is_game_version_in_file = true;
        }
    }
    void universe::set_universe_name(string temp) {
        if (!temp.empty()) {
            universe_name = temp;
            is_universe_name_in_file = true;
        }
    }
    void universe::set_gamerule(string temp) {
        int idx = 0, rule_flag = 0;
        if (temp[idx] != BIRTH) throw invalid_argument("incorrect input gamerules\n");
        idx++;
        while (idx < temp.size()) {
            if (temp[idx] == SLASH && !rule_flag) {
                rule_flag = 1;
                idx++;
                if ((idx == temp.size() - 1) || temp[idx] != SURVIVAL) throw invalid_argument("incorrect input gamerules\n");
                else idx++;
            }
            if (!isdigit(temp[idx]) || temp[idx] == NINE) throw invalid_argument("incorrect input gamerules\n");
            if (!rule_flag) gamerule_to_alive_count.push_back((int)(temp[idx] - '0'));
            else gamerule_to_survive_count.push_back((int)(temp[idx] - '0'));
            idx++;
        }
        is_gamerules_in_file = true;
    }
    void universe::set_length_width(string temp) {
        string first;
        string second;
        int number_flag = 0;
        for (int i = 0; i < temp.size(); ++i) {
            if (temp[i] == SPACE && !number_flag) {
                if (!i) throw invalid_argument("incorrect field size1 input\n");
                number_flag = 1;
                continue;
            }
            if (!isdigit(temp[i])) throw invalid_argument("incorrect field size2 input\n");
            if (!number_flag) first += temp[i];
            else second += temp[i];
        }
        length = stoi(first);
        width = stoi(second);
        is_length_width_in_file = true;
    }
    void universe::set_coords(string temp) {
        string first, second;
        int number_flag = 0;
        for (int i = 0; i < temp.size(); ++i) {
            if (temp[i] == SPACE && !number_flag) {
                if (!i) throw invalid_argument("incorrect coord1 input\n");
                number_flag = 1;
                continue;
            }
            if (!isdigit(temp[i])) throw invalid_argument("incorrect coord2 input\n");
            if (!number_flag) first += temp[i];
            else second += temp[i];
        }
        coords.resize(coords.size() + 1);
        coords[coords.size() - 1].resize(2);
        coords[coords.size() - 1][0] = stoi(first);
        coords[coords.size() - 1][1] = stoi(second);
        is_coords_in_file = true;
    }
    void universe::line_id(string temp, bool eof) {
        if (temp.empty() || temp.size() < 3) {
            if (eof) return;
            else throw invalid_argument("incorrect file format input\n");
        }
        string str_first_symbs = temp.substr(0, 3);
        if (str_first_symbs == GAME_VERSION_FIRST) {
            (*this).set_game_version(temp);
            return;
        }
        if (str_first_symbs == UNIVERSE_NAME_FIRST) {
            (*this).set_universe_name(temp.substr(3));
            return;
        }
        if (str_first_symbs == GAMERULES_FIRST) {
            (*this).set_gamerule(temp.substr(3));
            return;
        }
        if (!is_length_width_in_file) (*this).set_length_width(temp);
        else (*this).set_coords(temp);
    }
    void universe::input_check() {
        if (!is_game_version_in_file) {
            throw invalid_argument("file is missing game version\n");
        }
        if (!is_universe_name_in_file) {
            (*this).universe_name = DEFAULT_UNIVERSE_NAME;
            cout<<"file is missing a universe name\n";
        }
        if (!is_gamerules_in_file) {
            (*this).gamerule_to_alive_count = default_gamerule_to_alive_count;
            (*this).gamerule_to_survive_count = default_gamerule_to_survive_count;
            cout<<"file is missing game rules\n";
        }
        if (!is_length_width_in_file) {
            (*this).length = DEFAULT_LENGTH;
            (*this).width = DEFAULT_WIDTH;
            cout<<"file is missing a universe length and width\n";
        }
        if (!is_coords_in_file) {
            throw invalid_argument("file doesn't contain coords of live cells\n");
        }
    }
    string universe::get_universe_name() {
        return universe_name;
    }
    vector<int> universe::get_alive_rule() {
        return gamerule_to_alive_count;
    }
    vector<int> universe::get_survive_rule() {
        return gamerule_to_survive_count;
    }
    int universe::get_length() {
        return (*this).length;
    }
    int universe::get_width() {
        return (*this).width;
    }
}