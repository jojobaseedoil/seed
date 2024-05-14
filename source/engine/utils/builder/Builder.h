#pragma once

#include <type_traits>
#include <typeinfo>
#include <memory>

#include "../../entity/GameObject.h"
#include "../../scene/Scene.h"


/*
    https://www.tutorialspoint.com/cplusplus-equivalent-of-instanceof
*/
template<typename Base, typename T>
inline bool instanceof(const T *ptr) 
{
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

template<typename T>
class Builder
{
public:
    Builder(): entity(nullptr)
    {

    }

    template<typename... Args>
    void reset(Scene *scene, const std::string &layer, Args&&... args)
    {
        entity = new T(scene, layer, std::forward<Args>(args)...);
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

    void setComponents(Scene *scene, const std::vector<Component*> &components)
    {
        if(entity != nullptr)
        {
            for(Component *c : components)
            {
                entity->attach(c);

                if(instanceof<DrawComponent>(c))
                {
                    DrawComponent *drawable = dynamic_cast<DrawComponent*>(c);
                    scene->attach(drawable);
                }
            }
        }
    }

private:
    T *entity;

    static_assert(std::is_base_of<GameObject, T>::value, "T must be a GameObject.");
};