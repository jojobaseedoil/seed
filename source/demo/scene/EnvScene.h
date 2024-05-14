#pragma once

#include "../../engine/utils/builder/Director.h"

class EnvScene : public Scene
{
public:
    EnvScene(Game *game);
    ~EnvScene();

protected:
    void load() override;

private:
    Observer *mObserver;
};