#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <SDL2/SDL_stdinc.h>

#include "../component/Transform.h"
#include "../component/MonoBehaviour.h"
#include "../system/collision/CollisionSystem.h"

class Scene;
class Component;

class GameObject
{
public:
    friend class Scene;

    enum class State
    {
        Active, 
        Paused,
        Destroy
    };

    GameObject(Scene *scene);
    virtual ~GameObject();

    void Update(float deltaTime);

    template <typename T, typename... Args>
    T *AddComponent(Args&&... args);

    template<typename T>
    T *GetComponent();

    /* GameObject state */
    const State &GetState() const;
    static void Destroy(GameObject *entity);
    static void Activate(GameObject *entity);
    static void Pause(GameObject *entity);

public:

    Transform transform;
    const int tag;

protected:
    Scene *mScene;
    State mState;
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

    /* case is a monobehaviour, init script */
    MonoBehaviour* mb = dynamic_cast<MonoBehaviour*>(component);
    if(mb != nullptr)
    {
        CollisionSystem *csys = CollisionSystem::GetInstance();

        if(csys != nullptr)
        {
            csys->InsertScript(tag, mb);
        }

        mb->OnStart();
    }

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

template <typename Base, typename Derived>
bool IsInstanceOf(const Derived* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif // GAMEOBJECT_H