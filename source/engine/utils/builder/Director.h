#pragma once

#include "Builder.h"

/* gameobjects */
#include "../../entity/dummy/Poly.h"

/* components */ 
#include "../../component/Component.h"
#include "../../component/drawable/DrawPolygonComponent.h"
#include "../../component/rigidbody/RigidBody2DComponent.h"

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

    void build(Builder<Poly> &builder, const std::vector<Vector2> &vertices, const Color &color)
    {   
        /* create new entity */
        builder.reset(vertices, color);

        /* get entity */
        Poly *entity = builder.getProduct();

        /* add components */
        builder.setComponents({
            new DrawPolygonComponent(entity,vertices,color),
            new RigidBody2DComponent(entity)
        });

        mScene->attach(entity);
    }

private:
    Scene *mScene;
};