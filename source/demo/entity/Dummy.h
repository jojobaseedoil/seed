#pragma once

#include "../../engine/entity/GameObject.h"
#include "../../engine/utils/Color.h"

class Dummy : public GameObject
{
public:
    Dummy(Scene *scene, const std::string &layer="Dummy");

    void onProcessInput(const Uint8 *keyboard) override;
    void onUpdate(float dt) override;
    void onCollision(GameObject *other) override;
};