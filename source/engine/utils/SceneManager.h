#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <queue>
#include <unordered_map>

class GameObject;

class SceneManager
{
public:

    void ProcessPending();
    void UpdateEntities(float deltaTime);
    void ProcessDestroy();

    void Insert(GameObject *entity);
    void Remove(GameObject *entity);

    void DestroyEntities();

    std::vector<GameObject*> Entities() const;
private:

    std::queue<GameObject*> mPending;
    std::queue<GameObject*> mDestroy;

    std::unordered_map<int, GameObject*> mEntities;
};

#endif // SCENE_MANAGER_H