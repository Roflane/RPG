#pragma once
#include <raylib.h>
#include "../../../base/typedefs.h"

struct Gauge {
	static void drawGauge(float initValue, float currentValue, Rectangle gaugeRect, Color color);
	static void updateGauge(float initValue, float currentValue);
};