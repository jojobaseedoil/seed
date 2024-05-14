#pragma once

#include "Builder.h"
#include "../observer/Observer.h"

/* gameobjects */
#include "../../../demo/entity/Dummy.h"

/* components */ 
#include "../../component/drawable/DrawPolygonComponent.h"
#include "../../component/drawable/Sprite.h"

#include "../../component/rigidbody/RigidBody2DComponent.h"
#include "../../component/collider/AABB.h"

class Director
{
public:
    Director(Scene *scene) : mScene(scene)
    {

    }

    template<typename T>
    void build(const std::string &layer, float x, float y)
    {
        Builder<T> builder;

        T *entity = construct(builder, layer, x, y);

        mScene->attach(entity);
    }

private:

    Dummy *construct(Builder<Dummy> &builder, const std::string &layer, float x, float y)
    {   
        /* construct entity */
        builder.reset(mScene, layer);

        Dummy *entity = builder.getProduct();

        builder.setPosition(Vector2(x,y));

        /* add components */
        builder.setComponents(mScene,{
            new Sprite(entity),
            new RigidBody2DComponent(entity),
        });

        return entity;
    }

private:
    Scene *mScene;
};