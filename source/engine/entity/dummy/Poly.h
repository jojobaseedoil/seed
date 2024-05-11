#pragma once

#include "../GameObject.h"
#include "../../utils/Color.h"

class Poly : public GameObject
{
public:
    Poly(
        Scene *scene, 
        const std::vector<Vector2> &vertices, 
        const Color &col
    );

    void onProcessInput(const Uint8 *keyboard) override;

private:
    std::vector<Vector2> mVertices;
    Color mColor;
};