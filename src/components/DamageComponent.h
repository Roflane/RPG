#pragma once
#include "../entity/Entity.h"
#include "../stats/Stats.h"
#include "../../base/misc.h"
#include "../settings/GlobalSettings.h"

class Entity;

class DamageComponent {
private:
	Stats _stats;
	float _damage;
	bool _isCrit;
public:
	DamageComponent(Stats stats) : _stats(stats), _damage(), _isCrit(false) {}
	
	// Properties
	Stats& getDamageComponentStats()       { return _stats; }

	float getDamage() const				   { return _damage; }
	void setDamage(uint16 value)		   { _damage = value; }

	// Methods
	void update(Stats stats);
	void dealDamage(Entity &target);
	void dealDamageEnhanced(Entity &target);
	void dealDamageMagic(Entity &self, Entity &target);

	void displayDamageMark(Vector2 &pos, Color color);
};