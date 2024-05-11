#include "Scene.h"

#include "../utils/builder/Director.h"

#include <iostream>

Scene::Scene(Game *game):
    mGame       (game),
    mDirector   (nullptr),
    mIsUpdating (false)
{
    std::cout << "\tcreate 'Scene'.\n";
}

Scene::~Scene()
{
    std::cout << "\tdelete 'Scene'.\n";
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

}

/* cast actor into 'this' scene */
void Scene::attach(GameObject *actor)
{
    mActors.push_back(actor);
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
    mDirector = new Director(this);
    Builder<GameObject> builder(this);

    mDirector->build(builder);
    mDirector->build(builder);
}