#include "includes.h"

void InitPreSettings() {    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(GameSettings::targetFps);

    ScreenSettings::Init();
}

void InitPostSettings() {
    InitAudioDevice();
    GameSettings::InitSounds();

    SetExitKey(0);
    HideCursor();
}

void InitGraphics() {
    MiscAssets::Init();
    PlayerAssets::Init();
    FoeAssets::Init();
    WeaponAssets::Init();
    GearAssets::Init();
}


int main() {
    InitPreSettings();
    InitWindow(ScreenSettings::w, ScreenSettings::h, "RPG");
    InitPostSettings();
    InitGraphics();

    Game game;
    game.Menu();
}