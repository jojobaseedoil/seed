#include "Collider.h"

#include "../entity/GameObject.h"

Collider::Collider(bool isTrigger):
    isTrigger (isTrigger),
    isInside  (false)
{

}