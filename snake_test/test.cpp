#include "Source.cpp"
#include "doctest.h"
TEST_CASE("Testing apple placement")
{
    Game game;
    int field[field_size_x][field_size_y];
    for (int i = 0; i < field_size_x; i++)
    {
        for (int j = 0; j < field_size_y; j++)
        {
            game.field[i][j] = field_cell_type_none;
        }
    }
    int apple_count = rand() % 10 + 2;
    for (int i = 0; i < apple_count; i++)
    {
        game.apple_add();
    }
    bool flag = false;
    for (int i = 0; i < field_size_x; i++)
    {
        for (int j = 0; j < field_size_y; j++)
        {
            if (game.field[i][j] == field_cell_type_apple)
            {
                flag = true;
            }
        }
    }
    CHECK(flag);
}

TEST_CASE("Testing field eraser")
{
    std::vector <int> objects = { field_cell_type_none, field_cell_type_apple, field_cell_type_wall };
    Game game;
    for (int i = 0; i < field_size_x; i++)
    {
        for (int j = 0; j < field_size_y; j++)
        {
            game.field[i][j] = objects[rand()%objects.size()];
        }
    }
    game.clear_field();
    int apple_count = 0;
    for (int i = 0; i < field_size_x; i++)
    {
        for (int j = 0; j < field_size_y; j++)
        {
            if (game.field[i][j] == field_cell_type_apple)
            {
                apple_count++;
            }
        }
    }
    CHECK(apple_count == 1);
}

TEST_CASE("Testing snake length")
{
    Game game;
    for (int i = 0; i < field_size_x; i++)
    {
        for (int j = 0; j < field_size_y; j++)
        {
            game.field[i][j] = field_cell_type_none;
        }
    }
    game.field[0][1] = 1;
    game.field[0][2] = 2;
    game.field[0][3] = 3;
    game.field[0][4] = 4;
    game.increaseSnake();
    game.movement();
    CHECK(game.field[0][1]>0);
}

TEST_CASE("Testing basic game mechs")
{
    Game game;
    bool passed = true;
    for (int i = 0; i < field_size_x; i++)
    {
        for (int j = 0; j < field_size_y; j++)
        {
            game.field[i][j] = field_cell_type_none;
        }
    }
    for (int j = 0; j < 5; j++)
    {
        game.field[0][j] = j + 1;
    }
    game.field[0][5] = field_cell_type_apple;
    game.field[0][6] = field_cell_type_wall;
    game.movement();
    if (game.field[0][5] <= 0)
    {
        passed = false;
    }
    game.movement();
    if (game.field[0][2] > 0)
    {
        passed = false;
    }
    game.field[2][0] = 7;
    game.field[3][0] = 6;
    game.field[3][1] = 5;
    game.field[3][2] = 4;
    game.field[2][2] = 3;
    game.field[1][2] = 2;
    game.field[0][2] = 1;
    game.movement();
    game.movement();
    if (game.field[2][0] > 0) {
        passed = false;
    }
    CHECK(passed);
}

TEST_CASE("Testing snake movement")
{
    Game game;
    for (int i = 0; i < field_size_x; i++)
    {
        for (int j = 0; j < field_size_y; j++)
        {
            game.field[i][j] = field_cell_type_none;
        }
    }
    for (int j = 0; j < 5; j++)
    {
        game.field[0][j] = j + 1;
    }
    game.field[0][5] = field_cell_type_wall;
    game.movement();
    game.movement();
    game.movement();
    game.movement();
    bool req = (game.field[0][4] > 0 and game.field[1][5] > 0 and game.field[0][6] > 0);
    CHECK(req);
}