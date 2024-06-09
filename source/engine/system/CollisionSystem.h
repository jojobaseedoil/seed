#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "../component/Collider.h"

#include <vector>
#include <unordered_map>

class MonoBehaviour;
class GameObject;

const int NUM_LAYERS_2D = 32;
const int NUM_LAYERS_1D = 32*32;

class CollisionSystem
{
public:
    static CollisionSystem *GetInstance();

    /* Delete copy constructor and assignment operator */
    CollisionSystem(const CollisionSystem&) = delete;
    CollisionSystem &operator=(const CollisionSystem&) = delete;

    void InsertLayer(const Layer &layer, const std::vector<Layer> &collideWith={});
    void RemoveLayer(const Layer &layer);

    void InsertScript(int tag, const std::vector<MonoBehaviour*> &scripts);
    void RemoveScript(int tag);

    bool ShouldLayersCollide(const Layer &src, const Layer &tar);
    void BroadPhaseCollisionDetection(const std::vector<GameObject*> &entities);

private:
    CollisionSystem();

    void NarrowPhaseCollisionDetection(GameObject &src, GameObject &tar);
    void ResolveCollision(Collider &src, Collider &tar);
    void TriggerEnter(Collider &src, Collider &tar);
    void TriggerStay(Collider &src, Collider &tar);
    void TriggerExit(Collider &src, Collider &tar);
    void Reset();

private:
    static CollisionSystem *instance;

    bool mCollisionMatrix[NUM_LAYERS_1D]; // 32 layers max.
    std::unordered_map<int, std::vector<MonoBehaviour*>> mScripts;
};

#endif // COLLISION_SYSTEM_H