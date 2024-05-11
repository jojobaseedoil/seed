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
    for(GameObject *actor : mActors)
    {
        DrawComponent *drawable;
        drawable = actor->getComponent<DrawComponent>();

        if(drawable != nullptr && drawable->isEnabled())
        {
            drawable->draw(renderer);
        }
    }
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
    const std::vector<Vector2> vertices = {
        Vector2(0,0),
        Vector2(32,0),
        Vector2(32,32),
        Vector2(0,32)
    };

    const Color color(0xff,0,0,0xff);

    mDirector = new Director(this);
    Builder<Poly> builder(this);

    mDirector->build(builder, vertices, color);
    mDirector->build(builder, vertices, color);
}