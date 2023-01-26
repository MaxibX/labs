#include"gameconsole.h"

using namespace std;

namespace game {
    void console::choose_mode() {
        int mode;
        cout<<"Enter game mode: 1 == Online, 0 == Offline\n";
        cin>>mode;
        while (mode != ONLINE && mode != OFFLINE) {
            cout<<"Error entering gamemode, please try again\n";
            cin>>mode;
        }
        online_interface online;
        offline_interface offline;
        if (mode == ONLINE) launch_program(online);
        else launch_program(offline);
    }
    void console::launch_program(interface &mode) {
        string input_file_path;
        cout<<"Enter input file path:\n";
        cin>>input_file_path;
        mode.startgame(input_file_path);
    }
}