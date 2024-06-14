#include "CollisionSystem.h"

#include "../../entity/GameObject.h"

#include "../../component/MonoBehaviour.h"

#include <SDL2/SDL_log.h>
#include <algorithm>

CollisionSystem *CollisionSystem::instance = nullptr;

CollisionSystem *CollisionSystem::GetInstance() 
{
    if(instance == nullptr)
    {
        instance = new CollisionSystem;
    }

    return instance;
}

void CollisionSystem::Insert(Layer layer, Collider *collider)
{
    auto &colliders = mColliders[layer];
    auto it = std::find(colliders.begin(), colliders.end(), collider);
    
    if(it == colliders.end())
    {
        colliders.push_back(collider);
    }
}

void CollisionSystem::Remove(Layer layer, Collider *collider)
{
    auto it = mColliders.find(layer);

    if(it != mColliders.end())
    {
        auto &colliders = it->second;
        
        auto itc = std::find(
            colliders.begin(), 
            colliders.end(), collider
        );

        if(itc != colliders.end())
        {
            std::iter_swap(itc, colliders.end()-1);
            colliders.pop_back();

            if(colliders.empty())
            {
                mColliders.erase(layer);
            }
        }        
    }
}    

void CollisionSystem::InsertScript(int tag, MonoBehaviour *scr)
{
    mScripts[tag].push_back(scr);
}

void CollisionSystem::RemoveScripts(int tag)
{
    if(mScripts.find(tag) != mScripts.end())
    {
        mScripts.erase(tag);
    }
}

void CollisionSystem::BroadPhaseCollisionDetection(Collider *src)
{
    const std::vector<Layer> &layers = mCollideWith[src->layer];

    for(Layer layer : layers)
    {
        const std::vector<Collider*> &colliders = mColliders[layer];

        for(Collider *tar : colliders)
        {
            int t0 = src->mGameObject->tag;
            int t1 = tar->mGameObject->tag;

            if(src == tar)
            {
                continue;
            }
            
            NarrowPhaseCollisionDetection(src, tar);
        }
    }
}

void CollisionSystem::NarrowPhaseCollisionDetection(Collider *src, Collider *tar)
{
    /*
        if src don't colide with tar
        and tar is inside src
        call exit trigger
    */
    if(src->CheckCollision(*tar))
    {
        ResolveCollision(src, tar);
    } 
    else if( src->isInside(tar->mGameObject->tag) )
    {
        TriggerExit(src, tar);

        src->SetInside(-1);
    }
}

void CollisionSystem::TriggerEnter(Collider *src, Collider *tar)
{
    int tag = src->mGameObject->tag;

    for(MonoBehaviour *scr : mScripts[tag])
    {
        scr->OnTriggerEnter(*tar);
    }
}

void CollisionSystem::TriggerStay(Collider *src, Collider *tar)
{
    int tag = src->mGameObject->tag;

    for(MonoBehaviour *scr : mScripts[tag])
    {
        scr->OnTriggerStay(*tar);
    }
}

void CollisionSystem::TriggerExit(Collider *src, Collider *tar)
{
    int tag = src->mGameObject->tag;
 
    for(MonoBehaviour *scr : mScripts[tag])
    {
        scr->OnTriggerExit(*tar);
    }
}

void CollisionSystem::ResolveCollision(Collider *src, Collider *tar)
{
    /* 
        if tar is trigger 
        then check if src is inside tar
        if so, call trigger stay
        else call trigger enter and set tar inside src
    */
    if(tar->isTrigger)
    {
        int tarTag = tar->mGameObject->tag;

        if( src->isInside(tarTag) )
        {
            TriggerStay(src, tar);
        }
        else
        {
            TriggerEnter(src, tar);
            src->SetInside(tarTag);
        }
    }
    else
    {
        src->ResolveCollision(*tar);
    }

}

void CollisionSystem::SetCollisionAdj(const std::unordered_map<Layer, std::vector<Layer>> &mat)
{
    mCollideWith = mat;
}
