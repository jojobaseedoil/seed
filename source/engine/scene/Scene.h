#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL_render.h>

#include "../utils/SceneManager.h"

class Game;
class GameObject;

class Scene
{
public:
    Scene(Game *game, SDL_Renderer *renderer);
    virtual ~Scene();
    
    void Update(float deltaTime);

    void Insert(GameObject *entity);
    void Remove(GameObject *entity);

    void Start();

protected:
    virtual void Unload();
    virtual void Load();

public:
    SDL_Renderer *renderer;

protected:
    /* 'Scene' params */
    Game *mGame;

    SceneManager mManager;
};

#endif // SCENE_H