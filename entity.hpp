#pragma once
#include <raylib.h>

class Entity {
public:
    Vector2 position;
    bool active;

    virtual void Draw() = 0;
    virtual Rectangle getRect() = 0;
    virtual ~Entity() {}
};