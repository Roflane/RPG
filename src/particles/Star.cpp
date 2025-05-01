#include "Star.h"
#include "../../base/misc.h"

Star::Star(const char *spritePath, int8 starsCount) : _sprite(LoadTexture(spritePath)), _starsCount(starsCount) {
    _stars = new Vector2[starsCount];

    for (int8 i = 0; i < starsCount; i++) {
        _stars[i] = {
            GetRandomValueFloat(GetScreenWidth()),
            GetRandomValueFloat(GetScreenHeight())
        };
    }
}
Star::~Star() { delete[] _stars; }

void Star::Draw() {
    for (int8 i = 0; i < _starsCount; i++) {
        DrawTextureV(_sprite, _stars[i], WHITE);
    }
}

void Star::Update() {
    if (IsWindowResized()) {
        for (int8 i = 0; i < _starsCount; i++) {
            _stars[i] = {
                GetRandomValueFloat(GetScreenWidth()),
                GetRandomValueFloat(GetScreenHeight())
            };
        }
    }
}

void Star::Fall(float fallSpeed) {
    for (int8 i = 0; i < _starsCount; i++) {
        _stars[i].y += fallSpeed;

        if (_stars[i].y > GetScreenHeight()) {
            _stars[i].x = GetRandomValueFloat(GetScreenWidth());
            _stars[i].y = 0;
        }
    }
}