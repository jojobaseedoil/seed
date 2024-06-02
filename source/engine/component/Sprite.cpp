#include "Sprite.h"

#include <SDL2/SDL_image.h>

#include "../entity/GameObject.h"

Sprite::Sprite(SDL_Renderer *renderer, const std::string &sprite):
    Render(renderer)
{
    mTexture = Sprite::LoadTexture(renderer, sprite);
}

void Sprite::Draw()
{
    const Vector2 pos = mGameObject->transform.position;
    const Vector2 rot = mGameObject->transform.rotation;

    SDL_Rect dstRect = {
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        static_cast<int>(32.0f),
        static_cast<int>(32.0f)
    };

    SDL_RenderCopyEx(mRenderer, mTexture, nullptr, &dstRect, 0, nullptr, SDL_FLIP_NONE);
}

SDL_Texture *Sprite::LoadTexture(SDL_Renderer *renderer, const std::string &sprite)
{    
    SDL_Surface *surface = IMG_Load(sprite.c_str());

    if(surface == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "%s", IMG_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if(texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "%s", IMG_GetError());
        return nullptr;
    }

    return texture;
}