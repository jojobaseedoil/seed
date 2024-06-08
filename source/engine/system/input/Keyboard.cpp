#include "Keyboard.h"

#include "../../component/MonoBehaviour.h"

#include <SDL2/SDL_log.h>

Keyboard::Keyboard() : InputDevice(KEYBOARD)
{
    for(int i=0; i<SDL_NUM_SCANCODES; i++)
    {
        mKeyboardState[i] = false;
    }
}

void Keyboard::HandleInput(SDL_Event &event)
{
    int scancode = event.key.keysym.scancode;

    if(event.type == SDL_KEYDOWN)
    {
        mKeyboardState[scancode] = true;
        Notify(mOnPress, scancode);
    }
    else if(event.type == SDL_KEYUP)
    {
        mKeyboardState[scancode] = false;
        Notify(mOnRelease, scancode);
    }
}

void Keyboard::Bind(int scancode, const InputEvent &callable, int type)
{
    switch(type)
    {
    case SDL_KEYUP:
        mOnRelease[scancode] = callable;
        break;
    default:
        mOnPress[scancode] = callable;
        break;
    }
}

bool Keyboard::IsPressed(int scancode) const
{
    return mKeyboardState[scancode];
}