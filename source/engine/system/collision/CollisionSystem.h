#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "../../component/Collider.h"

#include <vector>
#include <unordered_map>

class MonoBehaviour;
class GameObject;

class CollisionSystem
{
public:
    static CollisionSystem *GetInstance();

    /* Delete copy constructor and assignment operator */
    CollisionSystem(const CollisionSystem&) = delete;
    CollisionSystem &operator=(const CollisionSystem&) = delete;

    void Insert(Layer layer, Collider *collider);
    void Remove(Layer layer, Collider *collider);

    void InsertScript(int tag, MonoBehaviour* scr);
    void RemoveScripts(int tag);

    void BroadPhaseCollisionDetection(Collider *src);

    void SetCollisionAdj(const std::unordered_map<Layer, std::vector<Layer>> &mat);

private:
    CollisionSystem() = default;

    void NarrowPhaseCollisionDetection(Collider *src, Collider *tar);
    void ResolveCollision(Collider *src, Collider *tar);
    void TriggerEnter(Collider *src, Collider *tar);
    void TriggerStay(Collider *src, Collider *tar);
    void TriggerExit(Collider *src, Collider *tar);

private:
    static CollisionSystem *instance;
    
    std::unordered_map<int, std::vector<MonoBehaviour*>> mScripts;
    std::unordered_map<Layer, std::vector<Collider*>> mColliders;
    std::unordered_map<Layer, std::vector<Layer>> mCollideWith;
};

#endif // COLLISION_SYSTEM_H