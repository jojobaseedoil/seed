#include "engine/game/Game.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define TITLE         "©jojobaseedoil, 2024"

int main(int argc, char **argv)
{
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

    if(game.start())
    {
        game.run();
    }
    game.shutdown();

    return 0;
}