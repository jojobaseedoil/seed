#include "EnvScene.h"

EnvScene::EnvScene(Game *game):
    Scene(game)
{
    mObserver = new Observer;
}

EnvScene::~EnvScene()
{
    delete mObserver;
}

void EnvScene::load()
{
    Director director(this);

    /* circ. info. */ 
    int cx = 100;
    int cy = 100;
    int r = 100;

    /* num squares */
    int squares = 1000;

    for(int i = 0; i < squares; i++)
    {
        float angle = (2 * M_PI / squares) * i;

        int x = cx + r * cos(angle);
        int y = cy + r * sin(angle);

        director.build<Dummy>("Instances", x, y);
    }
}