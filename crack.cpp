#include <filesystem>
#include <iostream>

#include "crack.h"

crack::crack(Game& game)
{
    handleApi(game);
}

void crack::handleApi(Game& game) {
    if (game.type == Game::TYPE::TOOL) {
        // eventually i just want to figure out if we dont NEED to crack it, such as the built in steam stuff like proton and redist
        std::cout << "type is tool, we wont be cracking these (yet)" << std::endl;
    } else {
        if (findApi(game.path, game)) {
            foundApi = true;
            std::cout << "FOUND API FOR " << game.id << " | " + game.apiPath << std::endl;
        } else {
            std::cout << "unable to find api file, game may require steamless" << std::endl;
        }
    }
}


// returns true if it found an api file, otherwise we'll talk steamless
bool crack::findApi(const std::filesystem::path& directory, Game& game) {
    // for every file in this directory
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        // if the file is a directory
        if (std::filesystem::is_directory(entry)) {
            findApi(entry, game); // Recursively search subdirectories
        }
        else {
            // otherwise test against filenames
            if(entry.path().filename() == "steam_api64.dll") {
                game.platform = Game::PLATFORM::WINDOWS64;
                game.apiPath = entry.path();
                return true;
            } else if (entry.path().filename() == "steam_api.dll") {
                game.platform = Game::PLATFORM::WINDOWS;
                game.apiPath = entry.path();
                return true;
            } else if (entry.path().filename() == "libsteam_api.so") {
                game.platform = Game::PLATFORM::LINUX;
                game.apiPath = entry.path();
                return true;
            }
        }
    }

    game.platform = Game::PLATFORM::UNKNOWN;
    return false;
}
