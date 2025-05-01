#pragma once
#include <raylib.h>
#include "../../base/typedefs.h"
#include "../../base/dirs.h"

struct PlayerAssets {
	inline static Texture2D spritesIdle[6];
	inline static Texture2D spritesUp[2], spritesDown[2];
	inline static Texture2D spritesLeft[12], spritesRight[12];

	inline static Texture2D CrimsonKatanaIdle[6];
	inline static Texture2D CrimsonKatanaBA[19];
	inline static Texture2D CrimsonKatanaEA[6];
	inline static Texture2D CrimsonKatanaBM[11];
	inline static Texture2D CrimsonKatanaEM[13];

	inline static Texture2D CelestialBowIdle[6];
	inline static Texture2D CelestialBowBA[9];
	inline static Texture2D CelestialBowEA[9];
	inline static Texture2D CelestialBowBM[9];
	inline static Texture2D CelestialBowEM[9];

	static void Init() {
		for (uint8 i = 0; i < 2; ++i) {
			spritesUp[i] = LoadTexture(Paths::Entity::Player::wipungUp[i]);
			spritesDown[i] = LoadTexture(Paths::Entity::Player::wipungDown[i]);
		}
		for (uint8 i = 0; i < 12; ++i) {
			spritesLeft[i] = LoadTexture(Paths::Entity::Player::wipungLeft[i]);
			spritesRight[i] = LoadTexture(Paths::Entity::Player::wipungRight[i]);
		}
		for (uint8 i = 0; i < 6; ++i) {
			spritesIdle[i] = LoadTexture(Paths::Entity::Player::wipungIdle[i]);
			CrimsonKatanaIdle[i] = LoadTexture(Paths::Entity::Player::CrimsonKatanaIdle[i]);
			CrimsonKatanaEA[i] = LoadTexture(Paths::Entity::Player::CrimsonKatanaEA[i]);
			CelestialBowIdle[i] = LoadTexture(Paths::Entity::Player::CelestialBowIdle[i]);
		}
		for (uint8 i = 0; i < 19; ++i) {
			CrimsonKatanaBA[i] = LoadTexture(Paths::Entity::Player::CrimsonKatanaBA[i]);
		}
		for (uint8 i = 0; i < 11; ++i) {
			CrimsonKatanaBM[i] = LoadTexture(Paths::Entity::Player::CrimsonKatanaBM[i]);
		}
		for (uint8 i = 0; i < 13; ++i) {
			CrimsonKatanaEM[i] = LoadTexture(Paths::Entity::Player::CrimsonKatanaEM[i]);
		}
		for (uint8 i = 0; i < 9; ++i) {
			CelestialBowBA[i] = LoadTexture(Paths::Entity::Player::CelestialBowBA[i]);
			CelestialBowEA[i] = LoadTexture(Paths::Entity::Player::CelestialBowEA[i]);
			CelestialBowBM[i] = LoadTexture(Paths::Entity::Player::CelestialBowBM[i]);
			CelestialBowEM[i] = LoadTexture(Paths::Entity::Player::CelestialBowEM[i]);
		}
	}
};
