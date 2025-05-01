#include "DamageComponent.h"

void DamageComponent::dealDamage(Entity &target) {
	float baseDamage = max<float>(0.0f, _stats.atk - target.getStat().def);
	float altDamage = max<float>(0.0f, _stats.edr - (1.0f + _stats.edb));
	_damage = baseDamage + altDamage;

	uint16 genCritValue = rand() % 100;
	_isCrit = genCritValue < static_cast<uint8>(_stats.cr); 
	if (_isCrit) {
		_damage *= 1.5f;
	}

	target.decreaseHp(_damage);
	printn(_damage);
}

void DamageComponent::dealDamageEnhanced(Entity &target) {
	float baseDamage = max<float>(0.0f, _stats.atk - target.getStat().def);
	float effectDamage = max<float>(0.0f, _stats.edr - (1.0f + _stats.edb));
	_damage = (baseDamage + effectDamage) * 2.0f;

	target.decreaseHp(_damage);
}

void DamageComponent::dealDamageMagic(Entity &self, Entity &target) {
	if (self.getStat().mana >= 7) {
		float baseDamage = max<float>(0.0f, _stats.atk - target.getStat().def);
		float altDamage = max<float>(0.0f, (1.0f + _stats.edb) - target.getStat().edr);
		_damage = baseDamage + altDamage;

		target.decreaseHp(_damage);
		self.decreaseMana(7);
	}
}

void DamageComponent::displayDamageMark(Vector2 &pos, Color color) {
	uint8 fontSize = 20;
	DrawText(TextFormat("%.0f", _damage), pos.x, pos.y, (_isCrit ? fontSize * 2 : fontSize), color);
}