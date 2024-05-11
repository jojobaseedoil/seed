#include "Scene.h"

#include "../entity/GameObject.h"
#include "../component/Component.h"

#include <iostream>

Scene::Scene(Game *game):
    mGame       (game),
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
void Scene::cast(GameObject *actor)
{
    mActors.push_back(actor);
}

/* specific load/unload scene */
void Scene::unload()
{
    for(GameObject *actor : mActors)
    {
        delete actor;
    }
}

void Scene::load()
{
    /*
        @test-scene

        Builder<GameObject> builder(this);

        for(int i=0; i<2; i++)
        {
            director.build(&builder);
            cast(builder.getProduct());
        }
    */
    
    /* actor mario */
    GameObject *mario = new GameObject(this);
    /* mario components */
    Component *draw = new Component(mario);
    Component *rigidbody = new Component(mario);

    mario->plug(draw);
    mario->plug(rigidbody);

    /* actor goomba */
    GameObject *goomba = new GameObject(this);
    /* goomba components */
    Component *drawAnim = new Component(goomba);
    Component *rigidbody2D = new Component(goomba);

    goomba->plug(drawAnim);
    goomba->plug(rigidbody2D);

    /* add mario and goomba into the scene */
    Scene::cast(mario);
    Scene::cast(goomba);
}