#include "SceneManager.h"

#include <algorithm>
#include "../entity/GameObject.h"


void SceneManager::ProcessPending()
{
    while( !mPending.empty() )
    {
        GameObject *entity = mPending.front();
        mPending.pop();

        if(entity != nullptr)
        {
            GameObject::Activate(entity);
            mEntities[entity->tag] = entity;
        }
    }
}

void SceneManager::UpdateEntities(float deltaTime)
{
    for(auto &[tag, entity] : mEntities)
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
}

void SceneManager::ProcessDestroy()
{
    while( !mDestroy.empty() )
    {
        GameObject *entity = mDestroy.front();
        mDestroy.pop();

        Remove(entity);

        delete entity;
    }
}

void SceneManager::Insert(GameObject *entity)
{
    switch (entity->GetState())
    {
    case GameObject::State::Pending:
        mPending.push(entity);
        break;
    case GameObject::State::Destroy:
        mDestroy.push(entity);
        break;
    default:
        mEntities[entity->tag] = entity;
        break;
    }
}

void SceneManager::Remove(GameObject *entity)
{
    mEntities.erase(entity->tag);
}

void SceneManager::DestroyEntities()
{
    for (auto &[tag, entity] : mEntities)
    {
        delete entity;
    }
    mEntities.clear();
}

std::vector<GameObject*> SceneManager::Entities() const
{
    std::vector<GameObject*> entities;

    for (auto it = mEntities.begin(); it != mEntities.end(); ++it)
    {
        entities.push_back(it->second); 
    }

    std::sort(entities.begin(), entities.end(), [](GameObject *a, GameObject *b){
        return a->tag < b->tag;
    });

    return entities;
}
