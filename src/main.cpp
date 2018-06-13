#include <iostream>
#include <stdexcept>
#include "game.h"

int main()
{
    using std::cerr;
    Game g;

    try{
        g.menu();
    }
    catch (Game::fileNotFoundException& e) {
        cerr << e.what();
        g.handleException(e);
        return EXIT_SUCCESS;
    }

    g.mainGame();

    return EXIT_SUCCESS;
}
