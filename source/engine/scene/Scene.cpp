#include "Scene.h"

#include <SDL2/SDL_log.h>

#include "../entity/GameObject.h"
#include "../component/Sprite.h"
#include "../component/RigidBody.h"

Scene::Scene(Game *game, SDL_Renderer *renderer):
    mGame       (game),
    renderer    (renderer),
    mIsUpdating (false)
{

}

Scene::~Scene()
{
    Unload();
}

void Scene::Update(float deltaTime)
{
    for(GameObject *entity : mEntities)
    {
        entity->Update(deltaTime);
    }
}

/* start new scene */
void Scene::Start()
{
    Unload(); // keeping the scene cohesive
    Load();
}

/* specific load/unload scene */
void Scene::Unload()
{
    for(GameObject *entity : mEntities)
    {
        delete entity;
    }
}

void Scene::Load()
{
    GameObject *mario = new GameObject();
    mario->AddComponent<Sprite>(renderer, "../assets/sprites/notex.png");
    mario->AddComponent<RigidBody>(1.0f, 10.0f, true);
    mEntities.push_back(mario);
}