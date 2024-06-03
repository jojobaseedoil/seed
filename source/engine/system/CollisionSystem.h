#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <string>
#include <unordered_map>

#include "../utils/IDManager.h"
#include "../component/Collider.h"

class GameObject;

constexpr int NUM_LAYERS = 32;

class CollisionSystem
{
public:
    CollisionSystem();

    void Insert(const std::string &layer, const std::vector<std::string> &collideWith={});
    void Remove(const std::string &layer);

    bool ShouldLayersCollide(const std::string &first, const std::string &second);
    void BroadPhaseCollisionDetection(const std::vector<GameObject*> &entities);
    void NarrowPhaseCollisionDetection(GameObject &first, GameObject &second);

    void ResolveCollision(Collider &first, Collider &second);

private:
    std::unordered_map<std::string, int> mLayer;
    bool mCollisionMatrix[NUM_LAYERS * NUM_LAYERS]; // 32 layers maximum
    IDManager mIdManager;
};

#endif // COLLISION_SYSTEM_H