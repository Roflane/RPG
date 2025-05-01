#include "GlobalSettings.h"

void GameSettings::InitSounds() {
    orbSound = LoadSound(Paths::Audio::orbSound);
    SetSoundVolume(orbSound, 0.3f);
}

float ScreenSettings::w;
float ScreenSettings::h;
float ScreenSettings::centerX;
float ScreenSettings::centerY;
Rectangle ScreenSettings::screen;

void ScreenSettings::Init() {
    w = 1140; h = 640;
    centerX = w / 2; centerY = h / 2;
    screen = { 0, 0, w, h };
}
void ScreenSettings::Update() {
    w = GetScreenWidth(); h = GetScreenHeight();
    centerX = w / 2; centerY = h / 2;
    screen = { 0, 0, w, h };
}
