#pragma once

#include <vector>
#include <string>

#include "../Component.h"
#include "../../utils/observer/Observer.h"

class ColliderComponent : public Component
{
public:
    ColliderComponent(GameObject *owner, Observer *obs);

    void update(float dt) override;

    virtual void resolve(GameObject *other) = 0;
    virtual bool intersect(GameObject *other) = 0;

    void scan(const std::string &layer, std::vector<GameObject*> &responses);

    void addLayersFrom(const std::vector<std::string> &layers);

private:
    std::vector<std::string> mLayers;
    Observer *mObserver;
};