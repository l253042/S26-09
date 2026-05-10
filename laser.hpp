#pragma once
#include "projectile.hpp"

class Laser : public Projectile {
public:

    Laser(Vector2 position, int speed);
    void Draw() override;
    void Update() override;
    Rectangle getRect() override;
};