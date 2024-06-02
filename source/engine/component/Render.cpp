#include "Render.h"

Render::Render(SDL_Renderer *renderer):
    mRenderer(renderer)
{

}

void Render::Draw()
{

}

void Render::Update(float deltaTime)
{
    Draw();
}