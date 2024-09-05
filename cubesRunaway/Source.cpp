#include "game.h"
#include <iostream>


int main(int argc, char* argv[])
{
    //random number generator identifyer
    std::srand(static_cast<unsigned>(time(NULL)));
    //the main game ooga booga
    Game game;
    while (game.running())
    {
        //the functions needed to make the game 
        game.update();
        game.render();

    }









    return 0;
}