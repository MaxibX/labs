#include "universe.h"
#include "gamefield.h"
#include "gameinterface.h"
#include "googletest-1.13.0/googletest/include/gtest/gtest.h"

using namespace std;

namespace game {
    TEST(GameTest, name_and_rules_from_file) {
        ifstream FILE;
        FILE.open("C:/Users/user/clionprojects/labs/lab2/test.txt");
        gamefield game(FILE);
        vector<int> game_rule_to_alive_count_t{1, 2, 3, 4, 5};
        vector<int> game_rule_to_survive_count_t{2, 4, 8};
        ASSERT_EQ(game.get_universe_name(), "test_name");
        ASSERT_EQ(game.get_survive_rule(), game_rule_to_survive_count_t);
        ASSERT_EQ(game.get_alive_rule(), game_rule_to_alive_count_t);
    }

    TEST(GameTest, alive_cells_from_file) {
        ifstream FILE;
        FILE.open("C:/Users/user/clionprojects/labs/lab2/cells.txt");
        gamefield game(FILE);
        ASSERT_EQ(game.get_cell(0, 0), ALIVE);
        ASSERT_EQ(game.get_cell(1, 0), ALIVE);
        ASSERT_EQ(game.get_cell(0, 1), ALIVE);
        ASSERT_EQ(game.get_cell(1, 1), ALIVE);
    }

    TEST(GameTest, height_and_width_from_file) {
        ifstream FILE;
        FILE.open("C:/Users/user/clionprojects/labs/lab2/height_width.txt");
        gamefield game(FILE);
        ASSERT_EQ(game.get_length(), 10);
        ASSERT_EQ(game.get_width(), 20);
    }

    TEST(GameTest, neightbours_count) {
        ifstream FILE;
        FILE.open("C:/Users/user/clionprojects/labs/lab2/nearby.txt");
        gamefield game(FILE);
        ASSERT_EQ(game.nearby_count(0, 0), 4);
        ASSERT_EQ(game.nearby_count(1, 0), 4);
        ASSERT_EQ(game.nearby_count(1, 1), 3);
        ASSERT_EQ(game.nearby_count(0, 1), 3);
        ASSERT_EQ(game.nearby_count(0, 3), 2);
    }

    TEST(GameTest, game_tick) {
        ifstream FILE;
        FILE.open("C:/Users/user/clionprojects/labs/lab2/tick.txt");
        gamefield game(FILE);
        game.tick(1);
        ASSERT_EQ(game.get_cell(0, 2), ALIVE);
        ASSERT_EQ(game.get_cell(1, 2), ALIVE);
        ASSERT_EQ(game.get_cell(2, 2), ALIVE);
        game.tick(1);
        ASSERT_EQ(game.get_cell(1, 1), ALIVE);
        ASSERT_EQ(game.get_cell(1, 2), ALIVE);
        ASSERT_EQ(game.get_cell(1, 3), ALIVE);
    }

    TEST(GameTest, dump_file) {
        ifstream FILE;
        FILE.open("C:/Users/user/clionprojects/labs/lab2/dump.txt");
        gamefield game(FILE);
        game.dump("C:/Users/user/clionprojects/labs/lab2/dump_out.txt");
        ifstream FILE_OUT;
        FILE_OUT.open("C:/Users/user/clionprojects/labs/lab2/dump_out.txt");
        gamefield temp(FILE_OUT);
        ASSERT_EQ(game.get_current_field(), temp.get_current_field());
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
