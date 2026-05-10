#pragma once
#include "entity.hpp"

class MysteryShip : public Entity {
public:
    MysteryShip();
    ~MysteryShip();
    void Draw() override;
    void Update();
    void Spawn();
    Rectangle getRect() override;
private:
    Texture2D image;  
    int speed;
};