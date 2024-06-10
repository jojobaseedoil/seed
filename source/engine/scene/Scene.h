#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL_render.h>
#include <queue>
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

    void AddEntity(GameObject *entity);
    void RemoveEntity(GameObject *entity);

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
    std::queue<GameObject*> mPendingEntities;
};

#endif // SCENE_H