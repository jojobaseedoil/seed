#ifndef TEXT_H
#define TEXT_H

#include "Render.h"
#include <string>
#include <SDL2/SDL_ttf.h>

struct TextAttributes
{
    const char   *text        = "Sample Text";
    const char   *fontFamily  = "../assets/fonts/Roboto-Regular.ttf";
    unsigned int  fontsize    = 24;
    SDL_Color     color       = {0xff,0xff,0xff,0xff};
    SDL_Point     position    = {20,20};
};

class Text : public Render
{
public:
    Text(SDL_Renderer *renderer, const TextAttributes &attrs);
    ~Text() override;

    void Draw() override;

    void SetText(const TextAttributes &newAttrs);

private:
    TextAttributes mAttr;
    TTF_Font      *mFont;
    SDL_Texture   *mTexture;
};

#endif // TEXT_H