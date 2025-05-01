#pragma once
#include <raylib.h>
#include "../../base/typedefs.h"
#include "../../base/dirs.h"

struct MiscAssets {
    inline static Texture2D cursors[4];
    inline static Texture2D backButtonSprite;

    static void Init() {
        for (uint8 i = 0; i < 4; ++i) {
            cursors[i] = LoadTexture(Paths::Misc::cursor[i]);
        }
        backButtonSprite = LoadTexture(Paths::Visual::Buttons::back);
    }
};
