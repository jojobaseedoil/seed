#include "DrawComponent.h"

DrawComponent::DrawComponent(GameObject *owner): Component(owner)
{

}

/* check if is component visible */
bool DrawComponent::isVisible() const
{
    return mIsVisible;
}

/* set component visible/invisible */
void DrawComponent::setVisible()
{
    mIsVisible = true;
}

void DrawComponent::setInvisible()
{
    mIsVisible = false;
}