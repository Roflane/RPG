#pragma once
#include "../assets/FoeAssets.h"
#include "../../base/misc.h"

class FoeAnimations {
public:
	FoeAnimations() = default;
	~FoeAnimations() = default;

	// Methods
	void KIdle(Texture2D &sprite, Vector2 pos, Color color);
	bool KBasicAttack(Texture2D &sprite, Vector2 pos, Color color);
	bool KBasicMagic(Texture2D &sprite, Vector2 pos, Color color);
};