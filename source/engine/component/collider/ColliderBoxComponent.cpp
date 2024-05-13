#include "ColliderBoxComponent.h"

#include "../../entity/GameObject.h"

ColliderBoxComponent::ColliderBoxComponent(
    GameObject *owner,
    Observer *obs,
    const Box &box
    // const Material &m    
):
    ColliderComponent (owner, obs),
    mBox              (box)
    // mMaterial         (m)
{

}
#include <iostream>
bool ColliderBoxComponent::intersect(GameObject *other)
{
    auto collider = other->getComponent<ColliderBoxComponent>();
    
    // if(collider == nullptr)
    // {
    //     std::cout << "null\n";
    // }

    // if(!collider->isEnabled())
    // {
    //     std::cout << "is not enabled\n";
    // }

    // if(this == collider)
    // {
    //     std::cout << "same\n";
    // }

    if( collider == nullptr || !collider->isEnabled() || this == collider)
    {
        return false;
    }
    // std::cout << "update!\n";
    return max().x > collider->min().x &&
           min().x < collider->max().x &&
           min().y < collider->max().y &&
           max().y > collider->min().y;
}

void ColliderBoxComponent::resolve(GameObject *other)
{

}

// bool ColliderBoxComponent::fit(ColliderBoxComponent *other) const
// {
//     if(mMaterial == Material::None || other->mMaterial == Material::None)
//     {
//         return true;
//     }
//     return static_cast<int>(mMaterial) + static_cast<int>(other->mMaterial) >= 5;
// }

Vector2 ColliderBoxComponent::min() const
{
    Vector2 pos = mOwner->position();

    return Vector2(mBox.x + pos.x, mBox.y + pos.y);
}

Vector2 ColliderBoxComponent::max() const
{
    return Vector2( min().x + mBox.w, min().y + mBox.h );
}

Vector2 ColliderBoxComponent::center() const
{
    return Vector2( min().x + mBox.w/2.0f, min().y + mBox.h/2.0f );
}