#pragma once
#include <raylib.h>
#include "../../base/typedefs.h"
#include "../../base/dirs.h"
#include "../stats/Stats.h"

enum GearParts : uint8 {
	HEAD,
	ARMOR, 
	BOOTS, 
	NECKLACE,
	RING
};

enum Gear : uint8 {
	T3HEAD,
	T3ARMOR,
	T3BOOTS, 
	T3NECKLACE,
	T3RING,
	T2HEAD,
	T2ARMOR,
	T2BOOTS,
	T2NECKLACE,
	T2RING,
	T1HEAD,
	T1ARMOR,
	T1BOOTS,
	T1NECKLACE,
	T1RING,
	NONEGEAR = 255
};