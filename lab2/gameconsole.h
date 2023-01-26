#ifndef LAB2_GAMECONSOLE_H
#define LAB2_GAMECONSOLE_H

#include"gameinterface.h"

namespace game {
    enum modes {
        OFFLINE = 0,
        ONLINE = 1
    };
    class console {
    public:
        void choose_mode();
        void launch_program(interface&);
    };
}

#endif //LAB2_GAMECONSOLE_H
