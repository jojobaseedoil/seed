#include "Scene.h"

#include <SDL2/SDL_log.h>

#include "../entity/GameObject.h"

#include "../component/Sprite.h"
#include "../component/RigidBody.h"
#include "../component/BoxCollider.h"
#include "../component/MonoBehaviour.h"

#include "../system/CollisionSystem.h"

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

    mCollisionSys.BroadPhaseCollisionDetection(mEntities);
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
    x->AddComponent<RigidBody>(1.0f, 10.0f, true);
    x->AddComponent<BoxCollider>(32,32);

    std::vector<MonoBehaviour*> xScr = {
        x->AddComponent<MonoBehaviour>()
    };

    /* PREFAB Y */
    y->AddComponent<Sprite>(renderer);
    y->AddComponent<RigidBody>(Math::Infinity, 0.0f, false);
    y->AddComponent<BoxCollider>(32,32,true);
    y->transform.position.y = 256.0f;

    std::vector<MonoBehaviour*> yScr = {
        y->AddComponent<MonoBehaviour>()
    };

    /* ADD MONOBEHAVIOUR TO COLLISION SYSTEM */
    mCollisionSys.InsertScript(x->tag, xScr);
    mCollisionSys.InsertScript(y->tag, yScr);

    /* ADD INTO COLLISION SYSTEM */
    mCollisionSys.InsertLayer(Instances, {Instances});

    /* ADD INTO GAME */
    mEntities.push_back(x);
    mEntities.push_back(y);
}