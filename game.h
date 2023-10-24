#ifndef GAME_H
#define GAME_H

#include <string>

class Game
{
public:
    Game();

    Game(int id, std::string name, std::string path);

    int id;
    std::string name;
    std::string path;
};

#endif // GAME_H
