#include "InputDevice.h"

#include "InputSystem.h"

InputDevice::InputDevice(Device tag) : 
    tag          (tag),
    sInputSystem (InputSystem::GetInstance())
{
    sInputSystem->AddDevice(this);
}

InputDevice::~InputDevice()
{
    sInputSystem->RemoveDevice(this);
}

void InputDevice::Notify(std::unordered_map<int, InputEvent> &binding, int key)
{
    if(binding.find(key) != binding.end())
    {
        InputEvent callback = binding[key];
        callback();
    }
}