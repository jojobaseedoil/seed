#pragma once

#include "Builder.h"
#include "../observer/Observer.h"

/* gameobjects */
#include "../../../demo/entity/Poly.h"

/* components */ 
#include "../../component/drawable/DrawPolygonComponent.h"
#include "../../component/rigidbody/RigidBody2DComponent.h"
#include "../../component/collider/AABB.h"

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


    void build(Builder<Poly> &builder, Observer *obs, const std::vector<Vector2> &vertices, const Color &color)
    {   
        /* create new entity */
        builder.reset(vertices, color);

        /* get entity */
        Poly *entity = builder.getProduct();

        obs->subscribe(entity->layer(), entity);

        /* add components */
        builder.setComponents({
            new DrawPolygonComponent(entity,vertices,color),
            new RigidBody2DComponent(entity),
            new AABB(entity, obs)
        });

        entity->getComponent<AABB>()->addLayersFrom({
            "Instances"
        });

        mScene->attach(entity);
    }

private:
    Scene *mScene;
};