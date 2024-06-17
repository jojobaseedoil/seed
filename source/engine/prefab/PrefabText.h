#ifndef PREFAB_TEXT_H
#define PREFAB_TEXT_H

#include "../entity/GameObject.h"
#include "../component/Text.h"

class PrefabText : public GameObject
{
public:
    PrefabText(Scene *scene, SDL_Renderer *renderer, const TextAttributes &attrs);
};

#endif // PREFAB_TEXT_H