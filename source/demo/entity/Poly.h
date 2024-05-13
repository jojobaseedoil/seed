#pragma once

#include "../../engine/entity/GameObject.h"
#include "../../engine/utils/Color.h"

class Poly : public GameObject
{
public:
    Poly(
        Scene *scene,
        const std::string &layer,
        const std::vector<Vector2> &vertices, 
        const Color &col
    );

    void onProcessInput(const Uint8 *keyboard) override;
    void onCollision(GameObject *other) override;

private:
    std::vector<Vector2> mVertices;
    Color mColor;
};