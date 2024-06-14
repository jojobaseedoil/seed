#include "Scene.h"

#include <SDL2/SDL_log.h>

#include "../entity/GameObject.h"

#include "../component/Text.h"
#include "../component/Sprite.h"
#include "../component/RigidBody.h"
#include "../component/BoxCollider.h"
// #include "../component/MonoBehaviour.h"
#include "../component/DebugBehaviour.h"

Scene::Scene(Game *game, SDL_Renderer *renderer):
    mGame            (game),
    renderer         (renderer)
{

}

Scene::~Scene()
{
    Unload();
}

void Scene::Update(float deltaTime)
{
    /* Scene routine */
    mManager.ProcessPending();
    mManager.UpdateEntities(deltaTime);
    mManager.ProcessDestroy();
}

void Scene::Insert(GameObject *entity)
{
    if(entity != nullptr)
    {
        entity->mScene = this;
        mManager.Insert(entity);
    }
}

void Scene::Remove(GameObject *entity)
{
    if(entity != nullptr)
    {
        mManager.Remove(entity);
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
    mManager.DestroyEntities();
}

void Scene::Load()
{
    GameObject *w = new GameObject;
    GameObject *x = new GameObject;
    GameObject *y = new GameObject;
    GameObject *z = new GameObject;

    /* PREFAB W */
    w->AddComponent<Sprite>(renderer);
    w->AddComponent<RigidBody>(1.0f, 10.0f, false);
    w->AddComponent<BoxCollider>(32, 32, Instances);
    w->AddComponent<DebugBehaviour>();
    
    /* PREFAB X */
    x->AddComponent<Sprite>(renderer);
    x->AddComponent<RigidBody>(10, 0.0f, false);
    x->AddComponent<BoxCollider>(32, 32, Background, true);

    x->transform.position.x = 256.0f;
    x->transform.position.y = 256.0f;

    /* PREFAB Y */
    y->AddComponent<Sprite>(renderer);
    y->AddComponent<RigidBody>(10, 0.0f, false);
    y->AddComponent<BoxCollider>(32, 32, Instances, false);

    y->transform.position.x = 512.0f;
    y->transform.position.y = 200.0f;

    /* PREFAB Z */
    TextAttributes attr = {"the quick brown fox jumps over the lazy dog"};
    z->AddComponent<Text>(renderer, attr);

    CollisionSystem *csys = CollisionSystem::GetInstance();

    csys->SetCollisionAdj({
        {Instances, {Instances}}
    });

    /* ADD INTO GAME */
    Insert(z);
    Insert(w);
    Insert(x);
    Insert(y);
}