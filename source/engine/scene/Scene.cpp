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
        switch ( entity->GetState() )
        {
        case GameObject::State::Active:
            entity->Update(deltaTime);
            break;

        case GameObject::State::Destroy:
            mDestroy.push(entity);
            break;
        
        default:
            break;
        }
    }

    /* Check for collisions */
    sCollisionSystem->BroadPhaseCollisionDetection(mEntities);

    /* insert new entities */
    InsertRoutine();
    
    /* delete entities */
    DestroyRoutine();
}

void Scene::AddEntity(GameObject *entity)
{
    entity->mScene = this;
    mPending.push(entity);
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
        delete mEntities.back();
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
    y->AddComponent<BoxCollider>(32,32,true);
    y->AddComponent<MonoBehaviour>();
    
    y->transform.position.x = 256.0f;
    y->transform.position.y = 256.0f;

    /* ADD INTO COLLISION SYSTEM */
    sCollisionSystem->InsertLayer(Instances, {Instances});

    /* ADD INTO GAME */
    AddEntity(x);
    AddEntity(y);
}

void Scene::InsertRoutine()
{
    while( !mPending.empty() )
    {
        GameObject *entity = mPending.front();
        mPending.pop();

        if(entity != nullptr)
        {
            GameObject::Activate(entity);
            mEntities.push_back(entity);
        }
    }
}

void Scene::DestroyRoutine()
{
    while( !mDestroy.empty() )
    {
        delete mDestroy.front();
        mDestroy.pop();
    }
}