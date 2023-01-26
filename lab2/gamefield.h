#include<iostream>
#include<vector>
#include"universe.h"

#ifndef LAB2_GAMEFIELD_H
#define LAB2_GAMEFIELD_H

using namespace std;

namespace game {
    const bool ALIVE = true, DEAD = false;
    class gamefield : public universe {
    public:
        gamefield(ifstream&);
        ~gamefield();
        void print_field();
        void set_life(int, int);
        int coord_mod(int, int);
        int nearby_count(int, int);
        void iteration();
        void tick(int);
        void dump(string);
        bool get_cell(int, int);
        vector<vector<bool>> get_current_field();

    private:
        vector<vector<int>> nearby;
        vector<vector<bool>> current_field;
    };
}

#endif //LAB2_GAMEFIELD_H
