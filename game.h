#ifndef GAME_H
#define GAME_H

#include <string>

class Game
{
public:
    enum class PLATFORM {
        LINUX,
        WINDOWS,
        WINDOWS64,
        UNKNOWN
    };

    enum class TYPE {
        GAME,
        TOOL,
        NODRM_PROTON,
        UNKNOWN
    };

    Game();

    Game(int id, std::string name, std::string path);

    int id;
    std::string name;
    std::string path;

    PLATFORM platform = PLATFORM::UNKNOWN;
    TYPE type = TYPE::UNKNOWN;

    std::string apiPath;

};

#endif // GAME_H
