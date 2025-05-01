#pragma once
#include <raylib.h>
#include "../../base/typedefs.h"
#include "../../base/dirs.h"

struct FoeAssets {
	inline static Texture2D idleK[6];

	inline static Texture2D idleKWeapon[6];
	inline static Texture2D KBasicAttackA[21];
	inline static Texture2D KBasicMagicA[10];

	static void Init() {
		for (uint8 i = 0; i < 6; ++i) {
			idleK[i] = LoadTexture(Paths::Entity::Enemy::idleK[i]);
			idleKWeapon[i] = LoadTexture(Paths::Entity::Enemy::idleKWeapon[i]);
		}
		for (uint8 i = 0; i < 21; ++i) {
			KBasicAttackA[i] = LoadTexture(Paths::Entity::Enemy::KBasicAttack[i]);
		}
		for (uint8 i = 0; i < 10; ++i) {
			KBasicMagicA[i] = LoadTexture(Paths::Entity::Enemy::KBasicMagic[i]);
		}
	}
};