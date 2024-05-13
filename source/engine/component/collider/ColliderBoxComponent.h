#pragma once

#include <SDL2/SDL_rect.h>

#include "ColliderComponent.h"
#include "../../utils/Math.h"

// enum class Material
// {
//     None,  /* Does not collide with any other layer */
//     Solid, /* Collides with Lock and Key layers */
//     Lock,  /* Collides with itself and the Solid layer */
//     Key    /* Collides with the Solid layer */
// };

struct Box
{
    float x, y;
    float w, h;
};

class ColliderBoxComponent : public ColliderComponent
{
public:
    ColliderBoxComponent(
        GameObject *owner,
        Observer *obs,
        const Box &box    = {0,0,32,32}
        // const Material &m = Material::Solid    
    );

    bool intersect(GameObject *other) override;
    void resolve(GameObject *other) override;

    // bool fit(ColliderBoxComponent *other) const;

    /* important points of the ColliderBoxComponent */
    Vector2 min() const;
    Vector2 max() const;
    Vector2 center() const;

private:
    Box mBox;
    // Material mMaterial;
};