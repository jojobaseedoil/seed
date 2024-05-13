#include "Scene.h"

#include <SDL2/SDL_log.h>

#include "../utils/builder/Director.h"

Scene::Scene(Game *game):
    mGame       (game),
    mDirector   (nullptr),
    mIsUpdating (false)
{
    SDL_Log("\tcreate 'Scene'.\n");
}

Scene::~Scene()
{
    SDL_Log("\tdelete 'Scene'.\n");
    Scene::unload();
}

/* update scene */
void Scene::processInput(const Uint8 *keyboard)
{
    for(GameObject *actor : mActors)
    {
        actor->processInput(keyboard);
    }
}

void Scene::update(float dt)
{
    for(GameObject *actor : mActors)
    {
        actor->update(dt);
    }
}

void Scene::draw(SDL_Renderer *renderer)
{
    for(DrawComponent *drawable : mDrawables)
    {
        if( drawable != nullptr && drawable->isEnabled() )
        {
            drawable->draw(renderer);
        }
    }
}

/* attach actor into 'this' scene */
void Scene::attach(GameObject *actor)
{
    mActors.push_back(actor);
}

/* attach drawable into 'this' scene */
void Scene::attach(DrawComponent *drawable)
{
    mDrawables.push_back(drawable);
}

/* start new scene */
void Scene::action()
{
    unload(); // keeping the scene cohesive
    load();
}

/* specific load/unload scene */
void Scene::unload()
{
    delete mDirector;

    for(GameObject *actor : mActors)
    {
        delete actor;
    }
}

void Scene::load()
{

}