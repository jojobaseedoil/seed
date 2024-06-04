#include "engine/game/Game.h"

const unsigned int SCREEN_WIDTH  = 800;
const unsigned int SCREEN_HEIGHT = 600;
const std::string  TITLE         = "seed - ©jojobaseedoil, 2024";

int main(int argc, char **argv)
{
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

    if(game.Start())
    {
        game.Run();
    }
    game.Shutdown();
}