#include "MonoBehaviour.h"

#include "../entity/GameObject.h"
#include <SDL2/SDL_log.h>

MonoBehaviour::~MonoBehaviour()
{

}

void MonoBehaviour::OnStart()
{

}

void MonoBehaviour::OnUpdate()
{

}

void MonoBehaviour::OnTriggerEnter(Collider &other)
{
    int me = mGameObject->tag;
    SDL_Log("OnTriggerEnter : me=%d, other=%d", me, other.GetTag());
}

void MonoBehaviour::OnTriggerStay(Collider &other)
{
    int me = mGameObject->tag;
    SDL_Log("OnTriggerStay : me=%d, other=%d", me, other.GetTag());
}

void MonoBehaviour::OnTriggerExit(Collider &other)
{
    int me = mGameObject->tag;
    SDL_Log("OnTriggerExit : me=%d, other=%d", me, other.GetTag());
}

void MonoBehaviour::OnDestroy()
{
    
}