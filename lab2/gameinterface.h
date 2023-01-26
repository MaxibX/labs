#include"gamefield.h"

#ifndef LAB2_GAMEINTERFACE_H
#define LAB2_GAMEINTERFACE_H

namespace game {
    class interface {
    public:
        virtual void startgame(string) = 0; //
    };
    class online_interface: public interface {
    public:
        void startgame(string) override;
        void print_help();
        void print_game_field_inf(gamefield&, int);
    };
    class offline_interface: public interface {
    public:
        void startgame(string) override;
    };
}

#endif //LAB2_GAMEINTERFACE_H
