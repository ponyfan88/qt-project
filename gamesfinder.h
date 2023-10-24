#ifndef GAMESFINDER_H
#define GAMESFINDER_H

#include <vector>
#include <string>

#include "game.h"

class gamesFinder
{
public:
    gamesFinder();
    void findGames(const std::string directoryPath);
    std::vector<Game> games;
};

#endif // GAMESFINDER_H
