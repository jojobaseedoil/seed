#include "Render.h"

#include "../utils/SceneManager.h"

#include <SDL2/SDL_log.h>

Render::Render(SDL_Renderer *renderer):
    mRenderer(renderer)
{
    /* add this drawable into current scene */
    SceneManager *manager = SceneManager::GetInstance();
    manager->InsertRender(this);
}

Render::~Render()
{
    /* remove this drawable from current scene */
    SceneManager *manager = SceneManager::GetInstance();
    manager->RemoveRender(this);
}

void Render::Draw()
{

}