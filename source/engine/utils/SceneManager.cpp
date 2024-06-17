#include "SceneManager.h"

#include <algorithm>

#include "../scene/Scene.h"
#include "../component/Render.h"
#include "../entity/GameObject.h"

SceneManager *SceneManager::instance = nullptr;

SceneManager::SceneManager():
    mCurrScene(nullptr)
{

}

SceneManager::~SceneManager()
{
    delete mCurrScene;
}

SceneManager *SceneManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new SceneManager;
    }

    return instance;
}

void SceneManager::Update(float deltaTime)
{
    if (mCurrScene != nullptr)
    {
        mCurrScene->Update(deltaTime);
    }
}

void SceneManager::Draw()
{
    if (mCurrScene != nullptr)
    {
        mCurrScene->Draw();
    }
}

void SceneManager::ChangeScene(Scene *newScene)
{
    /* clear current scene */
    if (instance->mCurrScene != nullptr)
    {
        delete instance->mCurrScene;
    }
    /* start new scene */
    instance->mCurrScene = newScene;
    instance->mCurrScene->Start();
}

void SceneManager::InsertEntity(GameObject *entity)
{
    if(mCurrScene != nullptr && entity != nullptr)
    {
        mCurrScene->mEntities.push_back(entity);      
    }
}

void SceneManager::RemoveEntity(GameObject *entity)
{
    if(mCurrScene != nullptr && entity != nullptr)
    {
        std::vector<GameObject*> &entities = mCurrScene->mEntities;

        auto it = std::find(entities.begin(), entities.end(), entity);

        if(it != entities.end())
        {
            std::iter_swap(it, entities.end()-1);
            entities.pop_back();
        }
    }
}

void SceneManager::InsertRender(Render *component)
{
    if(mCurrScene != nullptr && component != nullptr)
    {
        mCurrScene->mDrawables.push_back(component);  
    }
}

void SceneManager::RemoveRender(Render *component)
{
    if(mCurrScene != nullptr && component != nullptr)
    {
        std::vector<Render*> &drawables = mCurrScene->mDrawables;

        auto it = std::find(drawables.begin(), drawables.end(), component);

        if(it != drawables.end())
        {
            std::iter_swap(it, drawables.end()-1);
            drawables.pop_back();
        }
    } 
}