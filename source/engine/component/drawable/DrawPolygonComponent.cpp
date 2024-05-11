#include "DrawPolygonComponent.h"

#include <cmath>
#include <SDL2/SDL_render.h>

#include "../../entity/GameObject.h"

DrawPolygonComponent::DrawPolygonComponent(
    GameObject                 *owner, 
    const std::vector<Vector2> &vertices, 
    const Color                &color
):
    DrawComponent (owner),
    mVertices     (vertices),
    mColor        (color)
{

}

void DrawPolygonComponent::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);

    /* get transformer */
    Vector2 pos   = mOwner->position();
    Vector2 rot   = mOwner->rotation();
    Vector2 scale = mOwner->scale();

    // render Polygon
    size_t numVertices = mVertices.size();

    for (int i=0; i<numVertices; i++)
    {
        Vector2 u = mVertices[i];
        Vector2 v = mVertices[(i+1) % numVertices];

        int x1 = static_cast<int>(pos.x + (u.x * std::cos(rot.x) - u.y * std::sin(rot.x)) * scale.x);
        int y1 = static_cast<int>(pos.y + (u.x * std::sin(rot.x) + u.y * std::cos(rot.x)) * scale.y);
        int x2 = static_cast<int>(pos.x + (v.x * std::cos(rot.x) - v.y * std::sin(rot.x)) * scale.x);
        int y2 = static_cast<int>(pos.y + (v.x * std::sin(rot.x) + v.y * std::cos(rot.x)) * scale.y);

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

void DrawPolygonComponent::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    mColor.r = r;
    mColor.g = g;
    mColor.b = b;
    mColor.a = a;
}

void DrawPolygonComponent::setVertices(const std::vector<Vector2> &v)
{
    mVertices = v;
}

const std::vector<Vector2> &DrawPolygonComponent::getVertices() const
{
    return mVertices;
}