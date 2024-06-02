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

    void Reset()
    {
        entity = new T();
    }

    T *GetProduct()
    {
        return entity;
    }

private:
    T *entity;

    static_assert(std::is_base_of<GameObject, T>::value, "T must be a GameObject.");
};