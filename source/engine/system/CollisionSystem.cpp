#include "CollisionSystem.h"

#include "../entity/GameObject.h"
#include "../component/Collider.h"

#include <SDL2/SDL_log.h>

CollisionSystem::CollisionSystem()
{
    for(int i=0; i<NUM_LAYERS*NUM_LAYERS; i++)
    {
        mCollisionMatrix[i] = false;
    }
}

void CollisionSystem::Insert(const std::string &layer, const std::vector<std::string> &collideWith)
{
    if(mLayer.find(layer) == mLayer.end())
    {
        if(mIdManager.HasNext())
        {
            mLayer[layer] = mIdManager.Next();

            for(const std::string &other : collideWith)
            {
                Insert(other);

                if(mLayer.find(other) != mLayer.end())
                {
                    mCollisionMatrix[ mLayer[layer] * NUM_LAYERS + mLayer[other] ] = true;
                }
            }
        }
    }
}

void CollisionSystem::Remove(const std::string &layer)
{
    if(mLayer.find(layer) != mLayer.end())
    {
        int id = mLayer[layer];
        mIdManager.Refund(id);

        for(int j=0; j<NUM_LAYERS; j++)
        {
            mCollisionMatrix[ id * NUM_LAYERS + j ] = false;
            mCollisionMatrix[ j  * NUM_LAYERS + id] = false;
        }

        mLayer.erase(layer);
    }
}

bool CollisionSystem::ShouldLayersCollide(const std::string &first, const std::string &second)
{
    if(mLayer.find(first) == mLayer.end() || mLayer.find(second) == mLayer.end())
    {
        return false;
    }

    return mCollisionMatrix[ mLayer[first] * NUM_LAYERS + mLayer[second] ];
}

void CollisionSystem::BroadPhaseCollisionDetection(const std::vector<GameObject*> &entities)
{
    for(size_t i=0; i<entities.size(); i++)
    {
        for(size_t j=i+1; j<entities.size(); j++)
        {
            GameObject *first  = entities[i];
            GameObject *second = entities[j];

            if(ShouldLayersCollide(first->layer, second->layer))
            {
                NarrowPhaseCollisionDetection(*first, *second);
            }
        }
    }
}

void CollisionSystem::NarrowPhaseCollisionDetection(GameObject &first, GameObject &second)
{
    Collider *self = first.GetComponent<Collider>();
    
    if(self != nullptr)
    {
        Collider *other = second.GetComponent<Collider>();
        
        if(self->CheckCollision(*other))
        {
            SDL_Log("Success Collision Check!");
        }
    }
}