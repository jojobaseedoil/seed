#include "Scene.h"

#include <SDL2/SDL_log.h>

#include "../entity/GameObject.h"

#include "../component/Text.h"
#include "../component/Sprite.h"
#include "../component/RigidBody.h"
#include "../component/BoxCollider.h"
// #include "../component/MonoBehaviour.h"
#include "../component/DebugBehaviour.h"
#include "../component/BoxBehaviour.h"

#include "../prefab/PrefabText.h"

Scene::Scene(Game *game, SDL_Renderer *renderer):
    mGame    (game),
    renderer (renderer)
{

}

Scene::~Scene()
{
    Unload();
}

void Scene::Update(float deltaTime)
{
    for(auto it = mEntities.begin(); it != mEntities.end(); it++)
    {
        GameObject *entity = *it;

        switch (entity->GetState())
        {
        case GameObject::State::Active:
            entity->Update(deltaTime);
            break;

        case GameObject::State::Destroy:
            delete entity;
            break;
        
        default:
            /* case is paused, 
            do nothing */
            break;
        }
    }
}

void Scene::Draw()
{
    for(Render *drawable : mDrawables)
    {
        drawable->Draw();
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
    while(!mEntities.empty())
    {
        delete mEntities.back();
    }
}

void Scene::Load()
{
    GameObject *w = new GameObject(this);
    GameObject *x = new GameObject(this);
    GameObject *y = new GameObject(this);
    GameObject *a = new GameObject(this);
    GameObject *b = new GameObject(this);

    /* PREFAB W */
    w->AddComponent<Sprite>(renderer);
    w->AddComponent<RigidBody>(1.0f, 10.0f, false);
    w->AddComponent<BoxCollider>(32, 32, Player);
    w->AddComponent<DebugBehaviour>();
    
    /* PREFAB X */
    x->AddComponent<Sprite>(renderer);
    x->AddComponent<RigidBody>(10, 0.0f, false);
    x->AddComponent<BoxCollider>(32, 32, Background);

    x->transform.position.x = 256.0f;
    x->transform.position.y = 256.0f;

    /* PREFAB Y */
    y->AddComponent<Sprite>(renderer);
    y->AddComponent<RigidBody>(10, 0.0f, false);
    y->AddComponent<BoxCollider>(32, 32, Box, false);
    y->AddComponent<BoxBehaviour>();

    y->transform.position.x = 512.0f;
    y->transform.position.y = 200.0f;

    /* PREFAB Z */
    PrefabText *z = new PrefabText(this, renderer, TextAttributes());

    /* PREFAB A */
    a->AddComponent<Sprite>(renderer);
    a->AddComponent<RigidBody>(10, 0.0f, false);
    a->AddComponent<BoxCollider>(32, 32, Instances, true);

    a->transform.position.x = 400.0f;
    a->transform.position.y = 200.0f;

    /* PREFAB X */
    b->AddComponent<Sprite>(renderer);
    b->AddComponent<RigidBody>(10, 0.0f, false);
    b->AddComponent<BoxCollider>(32, 32, Instances);

    b->transform.position.x = 64.0f;
    b->transform.position.y = 128.0f;

    CollisionSystem *csys = CollisionSystem::GetInstance();

    csys->SetCollisionAdj({
        {Player, {Instances}           },
        {Box   , {Player, Instances}   }
    });
}