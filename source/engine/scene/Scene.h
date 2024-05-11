#pragma once

#include <vector>
#include <SDL2/SDL_stdinc.h>

class Game;
class SDL_Renderer;
class GameObject;
class DrawComponent;

class Scene
{
public:
    Scene(Game *game);
    ~Scene();
    
    /* update scene */
    void processInput(const Uint8 *keyboard);
    void update(float dt);
    void draw(SDL_Renderer *renderer);

    /* cast actor into 'this' scene */
    void cast(GameObject *actor);

    /* specific load/unload scene */
    virtual void unload();
    virtual void load();

private:
    /* 'Scene' params */
    Game *mGame;

    std::vector<GameObject*> mActors;
    std::vector<GameObject*> mPendingActors;
    std::vector<DrawComponent*> mDrawables;

    bool mIsUpdating;
};