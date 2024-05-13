#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL_stdinc.h>

#include "../utils/Transform.h"

class Scene;
class Component;
class ColliderComponent;

enum class State
{
    Active, Paused, Destroy
};

class GameObject
{
public:
    GameObject(Scene *scene, const std::string &layer="Instances");
    virtual ~GameObject();

    /* update game object */
    void processInput(const Uint8 *keyboard);
    void update(float dt);

    /* transform setters */
    void translate(const Vector2 &p);
    void rotate(const Vector2 &r);
    void scale(const Vector2 &s);

    /* transform getters */
    const Vector2 &position() const;
    const Vector2 &rotation() const;
    const Vector2 &scale() const;

    /* gameObject state */
    void setState(const State &state);
    const State &getState() const;

    /* attach component into 'this' GameObject */
    void attach(Component *c);

    /* search for a component of type T */
    template<typename T>
    T *getComponent()
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

    /* specific collision check */
    virtual void detectCollision();
    virtual void onCollision(GameObject *other);

    const std::string &layer() const;

protected:
    /* specific update */
    virtual void onProcessInput(const Uint8 *keyboard);
    virtual void onUpdate(float dt);

    /* 'GameObject' params */
    Scene *mScene;
    
    std::string mLayer;

    std::vector<Component*> mComponents;
    Transform mTransform;
    State mState;
};