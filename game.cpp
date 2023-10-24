#include "game.h"

Game::Game()
{
    this->id = 0;
    this->name = "nonexistant game";
    this->path = "trash:/";
}

Game::Game(int id, std::string name, std::string path) {
    this->id = id;
    this->name = name;
    this->path = path;
}
