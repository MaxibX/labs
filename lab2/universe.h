#ifndef LAB2_UNIVERSE_H
#define LAB2_UNIVERSE_H

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

namespace game {
    const char BIRTH = 'B';
    const char SURVIVAL = 'S';
    const char SLASH = '/';
    const char NINE = (char)(9 + '0');
    const char SPACE = ' ';
    const int DEFAULT_LENGTH = 10;
    const int DEFAULT_WIDTH = 20;
    const string CURRENT_VERSION = "#Life 1.06";
    const string GAME_VERSION_FIRST = "#Li";
    const string UNIVERSE_NAME_FIRST = "#N ";
    const string GAMERULES_FIRST = "#R ";
    const string DEFAULT_UNIVERSE_NAME = "DEFAULT_UNIVERSE";
    const vector<int> default_gamerule_to_alive_count = {3};
    const vector<int> default_gamerule_to_survive_count = {2, 3};
    class universe {
    public:
        ~universe();
        void set_game_version(string);
        void set_universe_name(string);
        void set_gamerule(string);
        void set_length_width(string);
        void set_coords(string);
        void line_id(string, bool);
        void input_check();
        string get_universe_name();
        vector<int> get_alive_rule();
        vector<int> get_survive_rule();
        int get_length();
        int get_width();

    protected:
        string game_version;
        string universe_name;
        int length;
        int width;
        bool is_game_version_in_file = false;
        bool is_universe_name_in_file = false;
        bool is_length_width_in_file = false;
        bool is_gamerules_in_file = false;
        bool is_coords_in_file = false;
        vector<int> gamerule_to_alive_count;
        vector<int> gamerule_to_survive_count;
        vector<vector<int>> coords;
    };
}

#endif //LAB2_UNIVERSE_H
