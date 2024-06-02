#pragma once

#include <vector>
#include <SDL2/SDL_render.h>

class Game;
class GameObject;

class Scene
{
public:
    Scene(Game *game, SDL_Renderer *renderer);
    virtual ~Scene();
    
    void Update(float deltaTime);

    template <typename T, typename... Args>
    T* AddPrefab(Args&&... args);

    void Start();

    SDL_Renderer *renderer;

protected:
    virtual void Unload();
    virtual void Load();

    /* 'Scene' params */
    Game *mGame;

    std::vector<GameObject*> mEntities;
    std::vector<GameObject*> mPendingEntities;

    bool mIsUpdating;
};