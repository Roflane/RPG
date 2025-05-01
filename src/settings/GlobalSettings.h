#pragma once
#include <raylib.h>
#include "../../base/typedefs.h"
#include "../../base/dirs.h"

struct GameSettings {
    inline static uint8 targetFps = 144;
    inline static Sound orbSound;
    inline static Music deepspace;

    //static void InitMusic();
    static void InitSounds();
};

struct ScreenSettings {
    static float w;
    static float h;
    static float centerX;
    static float centerY;
    static Rectangle screen;

    static void Init();
    static void Update();
};
