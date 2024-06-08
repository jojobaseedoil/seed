#include "InputSystem.h"

#include <SDL2/SDL_log.h>

InputSystem *InputSystem::sInputSystem = nullptr;

InputSystem *InputSystem::GetInstance() 
{
    if(sInputSystem == nullptr) 
    {
        sInputSystem = new InputSystem;
    }

    return sInputSystem;
}

void InputSystem::AddDevice(InputDevice *device)
{
    mDevices[device->tag].push_back(device);
}

void InputSystem::RemoveDevice(InputDevice *device) 
{
    auto it = mDevices.find(device->tag);
    
    if (it != mDevices.end()) 
    {
        auto& devices = it->second;
        auto deviceIt = std::find(devices.begin(), devices.end(), device);
        
        if (deviceIt != devices.end()) 
        {
            std::swap(*deviceIt, devices.back());
            devices.pop_back();

            if (devices.empty()) 
            {
                mDevices.erase(it);
            }
        }
    }
}

void InputSystem::HandleKeyboard(SDL_Event &event)
{
    for(InputDevice *keyboard : mDevices[KEYBOARD])
    {
        keyboard->HandleInput(event);
    }
}

void InputSystem::HandleMouse(SDL_Event &event)
{
    for(InputDevice *mouse : mDevices[MOUSE])
    {
        mouse->HandleInput(event);
    }
}