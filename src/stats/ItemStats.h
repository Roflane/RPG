#pragma once
#include "Stats.h"

namespace GearStats {
	inline static Stats t1head{ .hp = 120, .def = 25, .edr = 3,  .cdr = 25 };
	inline static Stats t1armor{ .hp = 240, .def = 40, .edr = 4,  .cdr = 15 };
	inline static Stats t1boots{ .hp = 100, .def = 12, .edr = 5,  .cdr = 35 };
	inline static Stats t1necklace{ .hp = 70,  .def = 7,  .edr = 1,  .cdr = 55 };
	inline static Stats t1ring{ .hp = 50, .atk = 20, .def = 4,  .edr = 1,  .cdr = 65 };

	inline static Stats t2head{ .hp = 80,  .def = 17, .edr = 2,  .cdr = 20 };
	inline static Stats t2armor{ .hp = 160, .def = 30, .edr = 2,  .cdr = 10 };
	inline static Stats t2boots{ .hp = 70,  .def = 9,  .edr = 3,  .cdr = 25 };
	inline static Stats t2necklace{ .hp = 50,  .def = 5,  .edr = 0,  .cdr = 45 };
	inline static Stats t2ring{ .hp = 35, .atk = 40, .def = 2,  .edr = 0,  .cdr = 50 };

	inline static Stats t3head{ .hp = 50,  .def = 10, .edr = 1,  .cdr = 15 };
	inline static Stats t3armor{ .hp = 100, .def = 20, .edr = 1,  .cdr = 5 };
	inline static Stats t3boots{ .hp = 40,  .def = 6,  .edr = 2,  .cdr = 15 };
	inline static Stats t3necklace{ .hp = 30,  .def = 3,  .edr = 0,  .cdr = 30 };
	inline static Stats t3ring{ .hp = 20, .atk = 60, .def = 1,  .edr = 0,  .cdr = 35 };
}
static Stats gearStats[] = {
	GearStats::t3head, GearStats::t3armor, GearStats::t3boots, GearStats::t3necklace, GearStats::t3ring,
	GearStats::t2head, GearStats::t2armor, GearStats::t2boots, GearStats::t2necklace, GearStats::t2ring,
	GearStats::t1head, GearStats::t1armor, GearStats::t1boots, GearStats::t1necklace, GearStats::t1ring
};

namespace WeaponStats {
	inline static Stats crimsonKatana{ .atk = 13, .edb = 10, .cr = 5, .cd = 50 };
	inline static Stats celestialBow{ .atk = 19, .edb = 8, .cr = 8, .cd = 75 };
}
static Stats weaponStats[] = {
	WeaponStats::crimsonKatana, WeaponStats::celestialBow
};