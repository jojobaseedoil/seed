#pragma once

#include <vector>
#include "DrawComponent.h"

#include "../../utils/Color.h"
#include "../../utils/Math.h"

class DrawPolygonComponent : public DrawComponent
{
public:
    DrawPolygonComponent(
        GameObject                 *owner, 
        const std::vector<Vector2> &vertices, 
        const Color                &color
    );

    void draw(SDL_Renderer *renderer) override;

    /* change polygon color */
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /* get/set polygon vertices */
    void setVertices(const std::vector<Vector2> &vertices);
    const std::vector<Vector2> &getVertices() const;

private:
    /* 'DrawPolygonComponent' params */
    std::vector<Vector2> mVertices;
    Color mColor;
};