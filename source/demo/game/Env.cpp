#include "Env.h"

#include "../scene/EnvScene.h"

Env::Env(int screenWidth, int screenHeight, const std::string &title):
    Game(screenWidth, screenHeight, title)
{
    SDL_Log("create 'Demo'.\n");
}

void Env::startScene()
{
    mScene = new EnvScene(this);
    mScene->action();
}