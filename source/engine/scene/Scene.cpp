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
    sCollisionSystem (CollisionSystem::GetInstance())
{

}

Scene::~Scene()
{
    Unload();
}

void Scene::Update(float deltaTime)
{
    /* Update entities */
    for(GameObject *entity : mEntities)
    {
        if(entity->GetState() == GameObject::State::Active)
        {
            entity->Update(deltaTime);
        }
    }
    /* Check for collisions */
    sCollisionSystem->BroadPhaseCollisionDetection(mEntities);

    /* insert new entities */
    while( !mPendingEntities.empty() )
    {
        GameObject *entity = mPendingEntities.front();
        mPendingEntities.pop();

        if(entity != nullptr)
        {
            entity->SetState(GameObject::State::Active);
            mEntities.push_back(entity);
        }
    }

    /* find unused entities */
    std::vector<GameObject*> toDestroy;

    for(GameObject *entity : mEntities)
    {
        if(entity->GetState() == GameObject::State::Destroy)
        {
            toDestroy.push_back(entity);
        }
    }

    /* destroy unused entities */
    for(GameObject *entity : toDestroy)
    {
        GameObject::Destroy(entity);
    }
}

void Scene::AddEntity(GameObject *entity)
{
    entity->mScene = this;
    mPendingEntities.push(entity);
}

void Scene::RemoveEntity(GameObject *entity)
{
    auto itEntities = std::find(mEntities.begin(), mEntities.end(), entity);

    if(itEntities != mEntities.end())
    {
        std::iter_swap(itEntities, mEntities.end()-1);
        mEntities.pop_back();
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
        GameObject::Destroy(mEntities.back());
    }
}

void Scene::Load()
{
    GameObject *x = new GameObject;
    GameObject *y = new GameObject;

    /* PREFAB X */
    x->AddComponent<Sprite>(renderer);
    x->AddComponent<RigidBody>(1.0f, 10.0f, false);
    x->AddComponent<BoxCollider>(32,32);
    x->AddComponent<DebugBehaviour>();

    /* PREFAB Y */
    y->AddComponent<Sprite>(renderer);
    y->AddComponent<RigidBody>(10, 0.0f, false);
    y->AddComponent<BoxCollider>(32,32);
    y->AddComponent<MonoBehaviour>();
    
    y->transform.position.x = 256.0f;
    y->transform.position.y = 256.0f;

    /* ADD INTO COLLISION SYSTEM */
    sCollisionSystem->InsertLayer(Instances, {Instances});

    /* ADD INTO GAME */
    AddEntity(x);
    AddEntity(y);
}