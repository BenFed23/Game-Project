#include "Player.h"
#include "Game.h"
#include "GameFiles.h"
#include "GameRun.h"
#include "utils.h"


int main(int argc, char* argv[])
{
    Game* g = nullptr;

    if (argc >= 2 && std::string(argv[1]) == "-load")
    {
        g = new GameFiles();   
        g->run();
        cls();
    }
    else
    {
        g = new GameRun();    
        g->Menu();
    }

    delete g;
    return 0;
}
