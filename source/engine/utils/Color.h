#pragma once

#include <SDL2/SDL_stdinc.h>

struct Color{
    Color(Uint8 r=0xff, Uint8 g=0xff, Uint8 b=0xff, Uint8 a=0xff):
        r(r), g(g), b(b), a(a) {}
    Uint8 r, g, b, a;
};