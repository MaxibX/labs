#include"gameinterface.h"

using namespace std;

namespace game {
    void online_interface::startgame(string path) {
        ifstream FILE;
        string command;
        int iterations = 0;
        FILE.open(path);
        if (!FILE.is_open()) {
            cout<<"can't open output file\n";
            FILE.close();
            FILE.open("test.txt");
        }
        gamefield game(FILE);
        cout<<"Enter the command (help == commands information)\n";
        while (true) {
            cin>>command;
            if (command == "help") (*this).print_help();
            else if (command == "tick") {
                int n;
                cin>>n;
                game.tick(n);
                iterations += n;
                (*this).print_game_field_inf(game, iterations);
            }
            else if (command == "dump") {
                string out_path;
                cin>>out_path;
                game.dump(out_path);
            }
            else if (command == "exit") {
                FILE.close();
                return;
            }
            else {
                cout<<"unrecognized command, please try again\n";
            }
        }
    }
    void online_interface::print_help() {
        cout<<"dump <path tp file> == save universe to file\n";
        cout<<"tick <n> == calculate n iterations and print the result\n";
        cout<<"exit == end the game\n";
    }
    void online_interface::print_game_field_inf(gamefield &field, int iteration) {
        cout<<field.get_universe_name()<<'\n';
        cout<<'B';
        vector<int> temp;
        temp = field.get_alive_rule();
        for (int i = 0; i < temp.size(); ++i) cout<<temp[i];
        cout<<"/S";
        temp = field.get_survive_rule();
        for (int i = 0; i < temp.size(); ++i) cout<<temp[i];
        cout<<'\n';
        cout<<"Iteration No. "<<iteration<<'\n';
        field.print_field();
        temp.clear();
    }
    void offline_interface::startgame(string path) {
        ifstream FILE;
        string command, out_path;
        int iterations;
        FILE.open(path);
        if (!FILE.is_open()) {
            cout<<"can't open input file\n";
            FILE.close();
            FILE.open("C:/Users/User/CLionProjects/labs/lab2/default.txt");
            //cout<<FILE.is_open();
        }
        gamefield game(FILE);
        cout<<"Enter number of iterations: \n";
        cin>>iterations;
        cout<<"Enter output file path: \n";
        cin>>out_path;
        game.tick(iterations);
        game.dump(out_path);
        FILE.close();
    }
}