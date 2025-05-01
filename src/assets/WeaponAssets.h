#pragma once
#include <raylib.h>
#include <vector>
#include "../../base/typedefs.h"
#include "../../base/dirs.h"

struct WeaponAssets {
	inline static Texture2D CrimsonKatana;
	inline static Texture2D CrimsonKatanaA[5];
	inline static Texture2D CurrentCrimsonKatanaA;

	inline static Texture2D CelestialBow;
	inline static Texture2D CelestialBowA[5];
	inline static Texture2D CurrentCelestialBowA;

	inline static Texture2D RapidNunchuks;
	inline static Texture2D RapidNunchuksA[5];

	inline static std::vector<Texture2D>  WeaponList;
	inline static std::vector<Texture2D*> CurrentAnimationList;

	static void Init() {
		CrimsonKatana = LoadTexture(Paths::Weapon::crimsonKatana);
		CelestialBow = LoadTexture(Paths::Weapon::celestialBow);
		RapidNunchuks = LoadTexture(Paths::Weapon::rapidNunchucks);
		WeaponList = { CrimsonKatana, CelestialBow, RapidNunchuks };

		for (int8 i = 0; i < 5; ++i) {
			CrimsonKatanaA[i] = LoadTexture(Paths::Weapon::crimsonKatanaA[i]);
			CelestialBowA[i] = LoadTexture(Paths::Weapon::celestialBowA[i]);
			RapidNunchuksA[i] = LoadTexture(Paths::Weapon::rapidNunchucksA[i]);
		}
		CurrentAnimationList = { CrimsonKatanaA, CelestialBowA, RapidNunchuksA };
	}
};