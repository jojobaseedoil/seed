#pragma once

#include "../../engine/game/Game.h"

class Game;

class Env : public Game
{
public:
    Env(int screenWidth, int screenHeight, const std::string &title="");
    
protected:
    void startScene() override;
};