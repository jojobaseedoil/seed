#pragma once

#include <vector>
#include <SDL2/SDL_stdinc.h>

class Game;
class SDL_Renderer;
class GameObject;
class DrawComponent;
class Director;

class Scene
{
public:
    Scene(Game *game);
    virtual ~Scene();
    
    /* update scene */
    void processInput(const Uint8 *keyboard);
    void update(float dt);
    void draw(SDL_Renderer *renderer);

    /* attach actor into 'this' scene */
    void attach(GameObject *actor);
    /* attach drawable into 'this' scene */
    void attach(DrawComponent *drawable);

    /* start new scene */
    void action();

protected:
    /* specific load/unload scene */
    virtual void unload();
    virtual void load();

    /* 'Scene' params */
    Game *mGame;

    Director *mDirector;

    std::vector<GameObject*> mActors;
    std::vector<GameObject*> mPendingActors;
    std::vector<DrawComponent*> mDrawables;

    bool mIsUpdating;
};