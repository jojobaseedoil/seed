#include "Text.h"

Text::Text(SDL_Renderer *renderer, const TextAttributes &attrs):
    Render   (renderer),
    mAttr    (attrs),
    mFont    (nullptr),
    mTexture (nullptr)
{
    mFont = TTF_OpenFont(mAttr.fontFamily, mAttr.fontsize);
    if(!mFont)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "%s", TTF_GetError());
    }

    SetText(mAttr);
}

Text::~Text()
{
    if(mFont != nullptr)
    {
        TTF_CloseFont(mFont);
    }
}

void Text::Draw()
{
    if (mTexture != nullptr)
    {
        int w, h;
        /* get texture dimensions */ 
        SDL_QueryTexture(mTexture, nullptr, nullptr, &w, &h);  
        /* define text position on screen */ 
        SDL_Rect dstRect = { mAttr.position.x, mAttr.position.y, w, h };  
        /* render text */
        SDL_RenderCopy(mRenderer, mTexture, nullptr, &dstRect);  
    }
}

void Text::SetText(const TextAttributes &newAttrs)
{
    mAttr = newAttrs;

    if(mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
    }
    SDL_Surface *surface = TTF_RenderText_Blended(mFont, mAttr.text, mAttr.color);
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);

    if(mTexture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "%s", TTF_GetError());
    }

    SDL_FreeSurface(surface);
}