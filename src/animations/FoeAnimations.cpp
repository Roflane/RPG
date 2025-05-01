#include "FoeAnimations.h"

void FoeAnimations::KIdle(Texture2D &sprite, Vector2 pos, Color color) {
    static int8 frameCounter = 0;
    static int8 frameDelay = 6 * 6;
    static int8 idx = 0;
    if (frameCounter % frameDelay == 0) {
        idx = (idx + 1) % 6;
    }
    ++frameCounter;
    sprite = FoeAssets::idleKWeapon[idx];
    DrawTexture(sprite, pos.x, pos.y, color);
}
bool FoeAnimations::KBasicAttack(Texture2D &sprite, Vector2 pos, Color color) {
    static uint8 frameCounter = 0;
    static uint8 frameDelay = 10;
    static uint8 idx = 0;

    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        idx++;
    }
    frameCounter++;

    if (idx < 21) {
        sprite = FoeAssets::KBasicAttackA[idx];
        DrawTexture(sprite, pos.x, pos.y, color);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}
bool FoeAnimations::KBasicMagic(Texture2D &sprite, Vector2 pos, Color color) {
    static uint8 frameCounter = 0;
    static uint8 frameDelay = 10;
    static uint8 idx = 0;

    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        idx++;
    }
    frameCounter++;

    if (idx < 10) {
        sprite = FoeAssets::KBasicMagicA[idx];
        DrawTexture(sprite, pos.x, pos.y, color);
        return false;
    }
    else {
        idx = 0;
        return true;
    }
}