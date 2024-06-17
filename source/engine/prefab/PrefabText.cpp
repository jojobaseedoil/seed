#include "PrefabText.h"

PrefabText::PrefabText(Scene *scene, SDL_Renderer *renderer, const TextAttributes &attrs):
    GameObject(scene)
{
    AddComponent<Text>(renderer, attrs);
}