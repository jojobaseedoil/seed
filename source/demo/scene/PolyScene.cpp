#include "PolyScene.h"

PolyScene::PolyScene(Game *game):
    Scene(game)
{
    mObserver = new Observer;
}

PolyScene::~PolyScene()
{
    delete mObserver;
}

const std::vector<Poly*> PolyScene::getPolygons() const
{
    return mPolygons;
}

void PolyScene::load()
{
    const std::vector<Vector2> vertices = {
        Vector2(0,0),
        Vector2(32,0),
        Vector2(32,32),
        Vector2(0,32)
    };
    const std::vector<Color> color = {
        Color(0xff,0,0,0xff),
        Color(0x0,0xff,0,0xff)
    };

    mDirector = new Director(this);
    Builder<Poly> builder(this);

    for(int i=0; i<2; i++)
    {
        mDirector->build(builder, mObserver, vertices, color[i]);
        mPolygons.push_back(builder.getProduct());
    }

    mPolygons[0]->translate(Vector2(128,0));
    mPolygons[1]->setState(State::Paused);
}