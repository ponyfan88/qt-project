#include <filesystem>
#include <iostream>
#include <fstream>

#include "gamesfinder.h"

gamesFinder::gamesFinder()
{

}

void gamesFinder::findGames(const std::string directoryPath) {
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        std::string fileName = entry.path().filename();
        std::string filePath = entry.path();


        if (fileName.size() > 4) {
            std::string ext = fileName.substr(fileName.size() - 4);

            if (ext == ".acf") {
                // we found a game!

                std::ifstream file;
                file.open(filePath);

                std::string line;

                Game myGame;

                std::string myName;
                std::string myId;
                std::string myPath;

                for (int i = 0; i < 7; i++) {
                    if (i == 2) {
                        std::getline(file, myId, '\n');
                    }
                    else if (i == 4) {
                        std::getline(file, myName, '\n');
                    }
                    else if (i == 6) {
                        std::getline(file, myPath, '\n');
                    } else {
                        std::getline(file, line, '\n');
                    }
                }

                myName = myName.substr(10, myName.length() - 11);
                myId = myId.substr(11, myId.length() - 12);
                myPath = myPath.substr(16, myPath.length() - 17);

                myGame.name = myName;
                myGame.id = std::stoi(myId);
                myGame.path = directoryPath + "common/" + myPath + "/";

                if (std::filesystem::exists(myGame.path + "toolmanifest.vdf")) {
                    myGame.type = Game::TYPE::TOOL;
                } else {
                    myGame.type = Game::TYPE::GAME;
                }

                games.push_back(myGame);

                std::cout << "found game " << myGame.name << " (" << myGame.id << ") at " << myGame.path << std::endl;
            }
        }
    }
}
