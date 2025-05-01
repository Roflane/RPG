#include "Foe.h"

static int8 frameCounter = 0;
static int8 frameDelay = 5;

void Foe::drawShadows() {
    int8 offset = 1;
    DrawTexture(__sprite, __pos.x + offset, __pos.y, Fade(BLACK, 0.3f));
}
void Foe::draw() {
    __sprite = FoeAssets::idleK[0];
    DrawTexture(__sprite, __pos.x, __pos.y, __color);
}