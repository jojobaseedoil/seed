#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <SDL2/SDL_stdinc.h>

#include "../component/Transform.h"

class Scene;
class Component;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    void Update(float deltaTime);

    template <typename T, typename... Args>
    T *AddComponent(Args&&... args);

    template<typename T>
    T *GetComponent();

    static void Destroy(GameObject *entity);

    Transform transform;
    
protected:    
    Scene *mScene;

    std::vector<Component*> mComponents;
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