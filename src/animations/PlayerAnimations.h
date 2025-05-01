#pragma once
#include "../assets/PlayerAssets.h"
#include "../../base/misc.h"

class PlayerAnimations {
public:
	PlayerAnimations() = default;
	~PlayerAnimations() = default;

	// Methods
	void CrimsonKatanaIdle(Texture2D &sprite, Vector2 pos);
	bool CrimsonKatanaBA(Texture2D &sprite, Vector2 pos);
	bool CrimsonKatanaBM(Texture2D &sprite, Vector2 pos);
	bool CrimsonKatanaEA(Texture2D &sprite, Vector2 pos);
	bool CrimsonKatanaEM(Texture2D &sprite, Vector2 pos);

	void CelestialBowIdle(Texture2D &sprite, Vector2 pos);
	bool CelestialBowBA(Texture2D &sprite, Vector2 pos);
	bool CelestialBowEA(Texture2D &sprite, Vector2 pos);
	bool CelestialBowBM(Texture2D &sprite, Vector2 pos);
	bool CelestialBowEM(Texture2D &sprite, Vector2 pos);
};