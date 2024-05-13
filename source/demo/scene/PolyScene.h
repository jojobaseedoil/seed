#pragma once

#include "../../engine/utils/builder/Director.h"

class PolyScene : public Scene
{
public:
    PolyScene(Game *game);
    ~PolyScene();

    const std::vector<Poly*> getPolygons() const;

protected:
    void load() override;

private:
    Observer *mObserver;
    std::vector<Poly*> mPolygons;
};