#include "CollisionSystem.h"

#include "../entity/GameObject.h"

#include "../component/MonoBehaviour.h"

#include <SDL2/SDL_log.h>

CollisionSystem::CollisionSystem()
{
    Reset();
}

void CollisionSystem::InsertLayer(const Layer &layer, const std::vector<Layer> &collideWith)
{
    for(const Layer &other : collideWith)
    {
        mCollisionMatrix[layer * NUM_LAYERS_2D + other] = true;
    }
}

void CollisionSystem::RemoveLayer(const Layer &layer)
{
    for(int j=0; j<NUM_LAYERS_2D; j++)
    {
        mCollisionMatrix[ layer * NUM_LAYERS_2D + j ] = false;
        mCollisionMatrix[ j * NUM_LAYERS_2D + layer ] = false;
    }
}

void CollisionSystem::Reset()
{
    for(int i=0; i<NUM_LAYERS_1D; i++)
    {
        mCollisionMatrix[i] = false;
    }
    mScripts.clear();
}

void CollisionSystem::InsertScript(int tag, const std::vector<MonoBehaviour*> &scripts)
{
    mScripts[tag] = scripts;
}

void CollisionSystem::RemoveScript(int tag)
{
    if(mScripts.find(tag) != mScripts.end())
    {
        mScripts.erase(tag);
    }
}

bool CollisionSystem::ShouldLayersCollide(const Layer &src, const Layer &tar)
{
    return mCollisionMatrix[ src * NUM_LAYERS_2D + tar ];
}

void CollisionSystem::BroadPhaseCollisionDetection(const std::vector<GameObject*> &entities)
{
    size_t numEntities = entities.size();

    for(size_t i=0; i<numEntities; i++)
    {
        for(size_t j=i+1; j<numEntities; j++)
        {
            GameObject *src = entities[i];
            GameObject *tar = entities[j];

            if(ShouldLayersCollide(src->layer, tar->layer))
            {
                NarrowPhaseCollisionDetection(*src, *tar);
            }
        }
    }
}

void CollisionSystem::NarrowPhaseCollisionDetection(GameObject &src, GameObject &tar)
{
    Collider *c0 = src.GetComponent<Collider>();
    Collider *c1 = tar.GetComponent<Collider>();

    if(c0 && c1 && c0->CheckCollision(*c1))
    {
        ResolveCollision(*c0, *c1);
    }
    else if(c1->isInside)
    { 
        TriggerExit(*c0, *c1);

        c1->isInside = false;
    } 
}

/* WARNING: if tag not in mScripts it will create 
a new entry { tag : [] } */
void CollisionSystem::TriggerEnter(Collider &src, Collider &tar)
{
    int tag = src.GetTag();

    for(MonoBehaviour *scr : mScripts[tag])
    {
        scr->OnTriggerEnter(tar);
    }
}

/* WARNING: if tag not in mScripts it will create 
a new entry { tag : [] } */
void CollisionSystem::TriggerStay(Collider &src, Collider &tar)
{
    int tag = src.GetTag();

    for(MonoBehaviour *scr : mScripts[tag])
    {
        scr->OnTriggerStay(tar);
    }
}

/* WARNING: if tag not in mScripts it will create 
a new entry { tag : [] } */
void CollisionSystem::TriggerExit(Collider &src, Collider &tar)
{
    int tag = src.GetTag();
 
    for(MonoBehaviour *scr : mScripts[tag])
    {
        scr->OnTriggerExit(tar);
    }
}

void CollisionSystem::ResolveCollision(Collider &src, Collider &tar)
{
    if(tar.isTrigger)
    {
        if(tar.isInside)
        {
            TriggerStay(src, tar);
        }
        else
        {
            TriggerEnter(src, tar);

            tar.isInside = true;
        }
    }
    else
    {
        src.ResolveCollision(tar);
    }
}