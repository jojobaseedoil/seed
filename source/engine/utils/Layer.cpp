#include "Layer.h"

Layer::Layer(): mDepth(0)
{

}

/* add/remove layers*/
void Layer::insert(const std::string &layer)
{
    if(mLayers.find(layer) == mLayers.end())
    {
        mLayers[layer] = mDepth++;
    }
}

void Layer::remove(const std::string &layer)
{
    if(mLayers.find(layer) != mLayers.end())
    {
        mLayers.erase(layer);
        mDepth--;
    }
}

/* get a certain layer id */
int Layer::operator[](const std::string &layer)
{
    return id(layer);
}

int Layer::id(const std::string &layer)
{
    auto it = mLayers.find(layer);

    if(it != mLayers.end())
    {
        return it->second;
    }

    return -1;
}

/* get all layers */ 
const std::unordered_map<std::string, int> &Layer::get() const
{
    return mLayers;
}

/* number of layers */
int Layer::len() const
{
    return mDepth;
}