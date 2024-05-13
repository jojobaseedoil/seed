#pragma once

#include "../../engine/game/Game.h"
#include "../scene/PolyScene.h"

class Demo : public Game
{
public:
    Demo(int screenWidth, int screenHeight, const std::string &title=""):
        Game(screenWidth, screenHeight, title)
    {
        SDL_Log("create 'Demo'.\n");
    }

protected:
    void startScene() override
    {
        mScene = new PolyScene(this);
        mScene->action();
    }
};