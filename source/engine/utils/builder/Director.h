#pragma once

#include "Builder.h"
#include "../observer/Observer.h"

class Director
{
public:
    Director(Scene *scene) : 
        mScene(scene)
    {

    }   

    template<typename T>
    T *Build(float x, float y)
    {
        Builder<T> builder;

        T *entity = Construct(builder, x, y);

        return entity;
    }

private:

    GameObject *Construct(Builder<GameObject> &builder, float x, float y)
    {   
        builder.Reset();

        GameObject *entity = builder.GetProduct();

        return entity;
    }

private:
    Scene *mScene;
};