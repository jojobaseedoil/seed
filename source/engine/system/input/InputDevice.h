#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include <SDL2/SDL_events.h>
#include <unordered_map>
#include <functional>

class InputSystem;

enum Device
{
    KEYBOARD,
    MOUSE,
    JOYSTICK
};

class InputDevice
{
public:
    using InputEvent = std::function<void()>;

    InputDevice(Device tag);
    virtual ~InputDevice();

    virtual void HandleInput(SDL_Event &event) = 0;
    void Notify(std::unordered_map<int, InputEvent> &binding, int key);

    const Device tag;

protected:
    InputSystem *sInputSystem;
};

#endif // INPUT_DEVICE_H