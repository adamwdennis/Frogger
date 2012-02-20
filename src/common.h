//file: common.h

#ifndef COMMON_H
#define COMMON_H
#include "Coord3.h"

const float M_PI = 3.14159265f;

struct Frog
{
	Coord3 position;
    float rotationAngle;
    Coord3 velocity;
    bool kicked;
};

enum Key
{
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_PLUS,
    KEY_MINUS,
    KEY_SPACE
};



#endif
