#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL_render.h>
#include "../system/CollisionSystem.h"

class Game;
class GameObject;
class InputSystem;

class Scene
{
public:
    Scene(Game *game, SDL_Renderer *renderer);
    virtual ~Scene();
    
    void Update(float deltaTime);

    template <typename T, typename... Args>
    T* AddPrefab(Args&&... args);

    void Start();

protected:
    virtual void Unload();
    virtual void Load();

public:
    SDL_Renderer *renderer;

protected:
    /* 'Scene' params */
    Game *mGame;

    CollisionSystem *sCollisionSystem;

    std::vector<GameObject*> mEntities;
    std::vector<GameObject*> mPendingEntities;

    bool mIsUpdating;
};

#endif // SCENE_H