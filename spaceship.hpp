#pragma once
#include "entity.hpp"
#include "laser.hpp"
#include <vector>

class Spaceship : public Entity {
public:
    Spaceship();
    ~Spaceship();
    void Update();
    void Draw() override;
    void MoveRight();
    void MoveLeft();
    void FireLaser();
    Rectangle getRect() override;
    void Reset();
    std::vector<Laser> lasers;
    bool isHit;
    float hitTime;
    
private:
    float scale = 0.10f;
    Texture2D image;
    double lastFireTime; 
    Sound laserSound;
};