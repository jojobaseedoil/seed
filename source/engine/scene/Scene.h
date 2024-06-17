#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL_render.h>
#include <vector>

#include "../utils/SceneManager.h"

class Game;
class Render;
class GameObject;

class Scene
{
friend class SceneManager; 

public:
    Scene(Game *game, SDL_Renderer *renderer);
    virtual ~Scene();
    
    void Start();

    void Update(float deltaTime);
    void Draw();

protected:
    virtual void Unload();
    virtual void Load();

public:
    SDL_Renderer *renderer;

protected:
    /* 'Scene' params */
    Game *mGame;

    std::vector<GameObject*> mEntities;
    std::vector<Render*>     mDrawables;
};

#endif // SCENE_H