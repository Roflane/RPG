#include "Gauge.h"

void Gauge::drawGauge(float initValue, float currentValue, Rectangle gaugeRect, Color color) {
    DrawRectangleRec(gaugeRect, WHITE);

    float ratio = currentValue / initValue; 
    Rectangle obscured = { gaugeRect.x, gaugeRect.y, gaugeRect.width * ratio, gaugeRect.height };
    DrawRectangleRec(obscured, color);
}

void Gauge::updateGauge(float initValue, float currentValue) {
	initValue = currentValue;
}