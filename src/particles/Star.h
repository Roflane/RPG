#pragma once
#include <raylib.h>
#include <stdlib.h>
#include "../../base/typedefs.h"
#include "../settings/GlobalSettings.h"

class Star {
private:
    Texture2D _sprite;
    Vector2 *_stars;
    int8 _starsCount;
public:
    Star(const char *spritePath, int8 starsCount);
    ~Star();

    void Draw();
    void Update();
    void Fall(float fallSpeed);
};