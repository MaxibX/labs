#include"gamefield.h"

using namespace std;

namespace game {
    gamefield::gamefield(ifstream &FILE) {
        string temp;
        while (!FILE.eof()) {
            getline(FILE, temp);
            line_id(temp, FILE.eof());
        }
        this->input_check();
        current_field = vector<vector<bool>>(length, vector<bool>(width));
        nearby = vector<vector<int>>(length, vector<int>(width));
        for (int i = 0; i < coords.size(); ++i) set_life(coords[i][0], coords[i][1]);
    }
    gamefield::~gamefield() {
        current_field.clear();
        nearby.clear();
    }
    int gamefield::coord_mod(int x, int y) {
        int result = (x + 1) % y;
        if (result) return result - 1;
        return y - 1;
    }
    void gamefield::print_field() {
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                if (!current_field[i][j]) cout<<'#';
                else cout<<'O';
            }
            cout<<'\n';
        }
    }
    void gamefield::set_life(int x, int y) {
        current_field[x][y] = ALIVE;
    }
    int gamefield::nearby_count(int x, int y) {
        return (current_field[coord_mod(x + 1 + length, length)][coord_mod(y + width, width)] +
                current_field[coord_mod(x - 1 + length, length)][coord_mod(y + width, width)] +
                current_field[coord_mod(x + 1 + length, length)][coord_mod(y + 1 + width, width)] +
                current_field[coord_mod(x + 1 + length, length)][coord_mod(y - 1 + width, width)] +
                current_field[coord_mod(x - 1 + length, length)][coord_mod(y + 1 + width, width)] +
                current_field[coord_mod(x - 1 + length, length)][coord_mod(y - 1 + width, width)] +
                current_field[coord_mod(x + length, length)][coord_mod(y + 1 + width, width)] +
                current_field[coord_mod(x + length, length)][coord_mod(y - 1 + width, width)]);
    }
    void gamefield::iteration() {
        for (int i = 0; i < length; ++i)
            for (int j = 0; j < width; ++j)
                nearby[i][j] = this->nearby_count(i, j);
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                if (current_field[i][j]) {
                    bool is_cell_survive = false;
                    for (int survive = 0; survive < gamerule_to_survive_count.size(); ++survive)
                        if (nearby[i][j] == gamerule_to_survive_count[survive]) is_cell_survive = true;
                    if (!is_cell_survive) current_field[i][j] = DEAD;
                }
                else {
                    for (int alive = 0; alive < gamerule_to_alive_count.size(); ++alive)
                        if (nearby[i][j] == gamerule_to_alive_count[alive]) set_life(i, j);
                }
            }
        }
    }
    void gamefield::tick(int n) {
        for (int i = 0; i < n; ++i) (*this).iteration();
    }
    void gamefield::dump(string path) {
        ofstream FILE;
        FILE.open(path);
        if (!FILE.is_open()) {
            cout<<"can't open output file\n";
            FILE.close();
            return;
        }
        FILE<<(*this).game_version<<'\n';
        FILE<<"#N "<<(*this).universe_name<<'\n';
        FILE<<"#R B";
        for (int i = 0; i < gamerule_to_alive_count.size(); ++i) FILE<<gamerule_to_alive_count[i];
        FILE<<"/S";
        for (int i = 0; i < gamerule_to_survive_count.size(); ++i) FILE<<gamerule_to_survive_count[i];
        FILE<<'\n';
        FILE<<length<<' '<<width<<'\n';
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                if (current_field[i][j]) FILE << i << ' ' << j << '\n';
            }
        }
        FILE.close();
    }
    bool gamefield::get_cell(int x, int y) {
        return (*this).current_field[x][y];
    }
    vector<vector<bool>> gamefield::get_current_field() {
        return (*this).current_field;
    }
}