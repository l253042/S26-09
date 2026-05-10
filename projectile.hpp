#pragma once
#include "entity.hpp"

class Projectile : public Entity {
public:
    int speed;

    Projectile(Vector2 position, int speed) {
        this->position = position;
        this->speed = speed;
        this->active = true;
    }

    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual Rectangle getRect() = 0;
    virtual ~Projectile() {}
};