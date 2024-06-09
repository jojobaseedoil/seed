#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "InputDevice.h"

class Game;

class InputSystem
{
public:
    static InputSystem* GetInstance();

    /* Delete copy constructor and assignment operator */ 
    InputSystem(const InputSystem&) = delete;
    InputSystem& operator=(const InputSystem&) = delete;
    
    void AddDevice(InputDevice *device);
    void RemoveDevice(InputDevice *device);
    void HandleKeyboard(SDL_Event &event);
    void HandleMouse(SDL_Event &event);
    
private:
    InputSystem() = default;

private:

    static InputSystem *instance;
    std::unordered_map<Device, std::vector<InputDevice*>> mDevices;
};

#endif // INPUT_SYSTEM_H