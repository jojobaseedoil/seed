#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

class Scene;
class Render;
class GameObject;

class SceneManager
{
public:
    ~SceneManager();

    static SceneManager *GetInstance();

    static void ChangeScene(Scene *newScene);
    
    void Update(float deltaTime);
    void Draw();

    /* Add/Remove entity into current scene */
    void InsertRender(Render *render);
    void RemoveEntity(GameObject *entity);
    /* Add/Remove entity from current scene */
    void InsertEntity(GameObject *entity);
    void RemoveRender(Render *component);

private:
    SceneManager();

    static SceneManager *instance;
    Scene *mCurrScene;
};
#endif // SCENE_MANAGER_H