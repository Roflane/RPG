#pragma once
#include "Entity.h"
#include "../../base/dirs.h"
#include "../settings/GlobalSettings.h"
#include "../components/DamageComponent.h"
#include "../assets/FoeAssets.h"

class Foe : public Entity, public DamageComponent {
public:
	~Foe() = default;
	Foe() : Entity(0, Vector2(0, 0), Stats(), Color()), DamageComponent(Stats()) {}
	Foe(const char* spritePath, Vector2 pos, Stats stats, Color color) : Entity(spritePath, pos, stats, color), DamageComponent(stats) {}

	// Methods
	void drawShadows() override;
	void draw() override;
};