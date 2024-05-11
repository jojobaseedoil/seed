#pragma once

#include <type_traits>
#include <memory>

#include "../../entity/GameObject.h"
#include "../../scene/Scene.h"

template<typename T>
class Builder
{
public:
    Builder(Scene *scene): 
        entity (nullptr),
        mScene (scene)
    {

    }

    template<typename... Args>
    void reset(Args&&... args)
    {
        entity = new T(mScene, std::forward<Args>(args)...);
    }

    T *getProduct()
    {
        return entity;
    }

    void setPosition(const Vector2 &p)
    {
        if(entity != nullptr)
        {
            entity->translate(p);
        }
    }

    void setRotation(const Vector2 &r)
    {
        if(entity != nullptr)
        {
            entity->rotate(r);
        }
    }

    void setScale(const Vector2 &s)
    {
        if(entity != nullptr)
        {
            entity->scale(s);
        }
    }

    void setState(const State &state)
    {
        if(entity != nullptr)
        {
            entity->setState(state);
        }
    }

    void setComponents(const std::vector<Component*> &components)
    {
        if(entity != nullptr)
        {
            for(Component *c : components)
            {
                entity->attach(c);
            }
        }
    }

private:
    T *entity;
    Scene *mScene;
    static_assert(std::is_base_of<GameObject, T>::value, "T must be a GameObject.");
};