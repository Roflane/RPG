#pragma once
#include <raylib.h>
#include <vector>
#include "../../base/typedefs.h"
#include "../../base/dirs.h"

struct GearAssets {
	inline static Texture2D T3[5];
	inline static Texture2D T2[5];
	inline static Texture2D T1[5];
	inline static std::vector<Texture2D> GearList;

	static void Init() {
		for (uint8 i = 0; i < 5; ++i) {
			T3[i] = LoadTexture(Paths::Gear::T3[i]);
			T2[i] = LoadTexture(Paths::Gear::T2[i]);
			T1[i] = LoadTexture(Paths::Gear::T1[i]);
		}
		GearList = {
			T3[0], T3[1], T3[2], T3[3], T3[4],
			T2[0], T2[1], T2[2], T2[3], T2[4],
			T1[0], T1[1], T1[2], T1[3], T1[4]
		};
	}
};