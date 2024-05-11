#pragma once

#include "Builder.h"
#include "../../component/Component.h"

class Director
{
public:
    Director(Scene *scene) : mScene(scene)
    {

    }

    void build(Builder<GameObject> &builder)
    {   
        /* create new entity */
        builder.reset();

        /* get entity */
        GameObject *entity = builder.getProduct();

        /* add components */
        builder.setComponents({
            new Component(entity)
        });

        mScene->attach(entity);
    }

private:
    Scene *mScene;
};