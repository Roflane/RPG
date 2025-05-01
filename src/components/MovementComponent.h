#pragma once
#include <cmath>
#include "../../base/misc.h"
#include "../../base/typedefs.h"
#include "../settings/GlobalSettings.h"

enum MovementDirection : uint8 {
    IDLE,
    UP,
    DOWN, 
    LEFT, 
    RIGHT
};

class MovementComponent {
protected:
    bool __canMove;
    float __moveSpeed;
    MovementDirection __dir;
public:
    MovementComponent(uint16 moveSpeed) : __moveSpeed(moveSpeed), __dir(IDLE), __canMove(true) {}
    
    // Properties
    bool getCanMove() const     { return __canMove; }
    void setCanMove(bool value) { __canMove = value; }

    void setDir(MovementDirection dir) { __dir = dir; }
    MovementDirection getDir() const   { return __dir; }
    
    // Methods
    void move(float& posX, float &posY, float dt);
};