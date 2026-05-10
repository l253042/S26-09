#pragma once
#include "entity.hpp"

class Alien : public Entity {

public:
    Alien(int type, Vector2 position);
    void Draw() override;
    void Update(int direction);
    int GetType();
    Rectangle getRect() override;
    static void UnloadImages();
    static Texture2D alienImages[3];
    int type;  
};