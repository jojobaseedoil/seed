#include "Scene.h"

#include <SDL2/SDL_log.h>

#include "../entity/GameObject.h"

#include "../component/Sprite.h"
#include "../component/RigidBody.h"
#include "../component/BoxCollider.h"
// #include "../component/MonoBehaviour.h"
#include "../component/DebugBehaviour.h"

Scene::Scene(Game *game, SDL_Renderer *renderer):
    mGame            (game),
    renderer         (renderer),
    mIsUpdating      (false),
    sCollisionSystem (CollisionSystem::GetInstance())
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

    sCollisionSystem->BroadPhaseCollisionDetection(mEntities);
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
    GameObject *x = new GameObject(Instances);
    GameObject *y = new GameObject(Instances);

    /* PREFAB X */
    x->AddComponent<Sprite>(renderer);
    x->AddComponent<RigidBody>(1.0f, 10.0f, false);
    x->AddComponent<BoxCollider>(32,32);

    std::vector<MonoBehaviour*> xScr = {
        x->AddComponent<DebugBehaviour>()
    };

    /* PREFAB Y */
    y->AddComponent<Sprite>(renderer);
    y->AddComponent<RigidBody>(10, 0.0f, false);
    y->AddComponent<BoxCollider>(32,32);
    
    y->transform.position.x = 256.0f;
    y->transform.position.y = 256.0f;

    std::vector<MonoBehaviour*> yScr = {
        y->AddComponent<MonoBehaviour>()
    };

    /* ADD MONOBEHAVIOUR TO COLLISION SYSTEM */
    sCollisionSystem->InsertScript(x->tag, xScr);
    sCollisionSystem->InsertScript(y->tag, yScr);

    /* ADD INTO COLLISION SYSTEM */
    sCollisionSystem->InsertLayer(Instances, {Instances});

    /* ADD INTO GAME */
    mEntities.push_back(x);
    mEntities.push_back(y);
}