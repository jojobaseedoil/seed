#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <SDL2/SDL_stdinc.h>

#include "../component/Transform.h"

class Scene;
class Component;

class GameObject
{
public:
    GameObject(const Layer &layer=Layer::Instances);
    virtual ~GameObject();

    void Update(float deltaTime);

    template <typename T, typename... Args>
    T *AddComponent(Args&&... args);

    template<typename T>
    T *GetComponent();

    static void Destroy(GameObject *entity);


public:
    Transform transform;
    const Layer layer;
    const int tag;

protected:    
    Scene *mScene;

    std::vector<Component*> mComponents;

private:
    static int sNextId;
};

template <typename T, typename... Args>
T *GameObject::AddComponent(Args&&... args)
{
    T* component = new T(std::forward<Args>(args)...);
    component->mGameObject = this;
    mComponents.emplace_back(component);
    return component;
}

template<typename T>
T *GameObject::GetComponent()
{
    for(Component *c : mComponents)
    {
        T *t = dynamic_cast<T*>(c);

        if(t != nullptr)
        {
            return t;
        }
    }

    return nullptr;
}

#endif // GAMEOBJECT_H