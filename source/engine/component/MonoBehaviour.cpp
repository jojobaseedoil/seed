#include "MonoBehaviour.h"

MonoBehaviour::MonoBehaviour()
{
    OnStart();
}

MonoBehaviour::~MonoBehaviour()
{
    OnDestroy();
}

void MonoBehaviour::OnStart()
{

}

void MonoBehaviour::OnUpdate()
{

}

void MonoBehaviour::OnTriggerEnter(Collider &other)
{

}

void MonoBehaviour::OnTriggerStay(Collider &other)
{

}

void MonoBehaviour::OnTriggerExit(Collider &other)
{

}

void MonoBehaviour::OnDestroy()
{
    
}