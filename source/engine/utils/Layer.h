#pragma once

#include <string>
#include <unordered_map>

class Layer
{
public:
    Layer();

    /* add/remove layers*/
    void insert(const std::string &layer);
    void remove(const std::string &layer);

    /* get a certain layer id */
    int operator[](const std::string &layer);
    int id(const std::string &layer);

    /* get all layers */
    const std::unordered_map<std::string, int> &get() const;

    /* number of layers */
    int len() const;

private:
    /* @attributes */
    std::unordered_map<std::string, int> mLayers;
    int mDepth;
};