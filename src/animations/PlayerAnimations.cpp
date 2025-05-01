#include "PlayerAnimations.h"

static uint8 _zero = 0;
static uint8 frameCounter = 0;
static uint8 frameDelay = 10;

void PlayerAnimations::CrimsonKatanaIdle(Texture2D &sprite, Vector2 pos) {
    AnimateSprite(sprite, PlayerAssets::CrimsonKatanaIdle, pos, 6, 36, _zero, WHITE);
}
bool PlayerAnimations::CrimsonKatanaBA(Texture2D &sprite, Vector2 pos) {
    static uint8 idx = 0;
    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        ++idx;
    }
    ++frameCounter;
    if (idx < 19) {
        sprite = PlayerAssets::CrimsonKatanaBA[idx];
        DrawTexture(sprite, pos.x, pos.y, WHITE);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}
bool PlayerAnimations::CrimsonKatanaEA(Texture2D &sprite, Vector2 pos) {
    static uint8 idx = 0;
    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        ++idx;
    }
    ++frameCounter;
    if (idx < 6) {
        sprite = PlayerAssets::CrimsonKatanaEA[idx];
        DrawTexture(sprite, pos.x, pos.y, WHITE);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}
bool PlayerAnimations::CrimsonKatanaBM(Texture2D &sprite, Vector2 pos) {
    static uint8 idx = 0;
    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        ++idx;
    }
    ++frameCounter;
    if (idx < 11) {
        sprite = PlayerAssets::CrimsonKatanaBM[idx];
        DrawTexture(sprite, pos.x, pos.y, WHITE);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}
bool PlayerAnimations::CrimsonKatanaEM(Texture2D &sprite, Vector2 pos) {
    static uint8 idx = 0;
    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        ++idx;
    }
    ++frameCounter;
    if (idx < 13) {
        sprite = PlayerAssets::CrimsonKatanaEM[idx];
        DrawTexture(sprite, pos.x, pos.y, WHITE);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}

void PlayerAnimations::CelestialBowIdle(Texture2D &sprite, Vector2 pos) {
    AnimateSprite(sprite, PlayerAssets::CelestialBowIdle, pos, 6, 18, _zero, WHITE);
}
bool PlayerAnimations::CelestialBowBA(Texture2D &sprite, Vector2 pos) {
    static uint8 idx = 0;
    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        ++idx;
    }
    ++frameCounter;
    if (idx < 9) {
        sprite = PlayerAssets::CelestialBowBA[idx];
        DrawTexture(sprite, pos.x, pos.y, WHITE);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}
bool PlayerAnimations::CelestialBowEA(Texture2D &sprite, Vector2 pos) {
    static uint8 idx = 0;
    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        ++idx;
    }
    ++frameCounter;
    if (idx < 9) {
        sprite = PlayerAssets::CelestialBowEA[idx];
        DrawTexture(sprite, pos.x, pos.y, WHITE);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}
bool PlayerAnimations::CelestialBowBM(Texture2D &sprite, Vector2 pos) {
    static uint8 idx = 0;
    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        ++idx;
    }
    ++frameCounter;
    if (idx < 9) {
        sprite = PlayerAssets::CelestialBowBM[idx];
        DrawTexture(sprite, pos.x, pos.y, WHITE);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}
bool PlayerAnimations::CelestialBowEM(Texture2D &sprite, Vector2 pos) {
    static uint8 idx = 0;
    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        ++idx;
    }
    ++frameCounter;
    if (idx < 9) {
        sprite = PlayerAssets::CelestialBowEM[idx];
        DrawTexture(sprite, pos.x, pos.y, WHITE);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}