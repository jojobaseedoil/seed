#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "InputDevice.h"

class Keyboard : public InputDevice
{
public:
    Keyboard();
    void HandleInput(SDL_Event &event);
    void Bind(int scancode, const InputEvent &callable, int type=SDL_KEYDOWN);

    bool IsPressed(int scancode) const;
    
private:
    std::unordered_map<int, InputEvent> mOnPress;
    std::unordered_map<int, InputEvent> mOnRelease;

    bool mKeyboardState[SDL_NUM_SCANCODES];
};

#endif // KEYBOARD_H