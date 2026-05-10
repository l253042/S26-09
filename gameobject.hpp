#pragma once

class GameObject {
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void HandleInput() = 0;
    virtual ~GameObject() {}
};