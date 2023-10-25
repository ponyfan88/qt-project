#ifndef CRACK_H
#define CRACK_H

#include "game.h"
#include <filesystem>

class crack
{
public:
    crack(Game& game);
    void handleApi(Game& game);
    bool findApi(const std::filesystem::path& directory, Game& game);

    bool foundApi = false;
};

#endif // CRACK_H
