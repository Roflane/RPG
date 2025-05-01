#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "../base/typedefs.h"

template<typename... VA>
void prints(VA... va_args) {
	((std::cout << va_args << ' '), ...);
}

template<typename... VA>
void printn(VA... va_args) {
	((std::cout << va_args << '\n'), ...);
}

template <typename T>
T max(T value1, T value2) {
	return (value1 > value2) ? value1 : value2;
}
template <typename T>
T min(T value1, T value2) {
	return (value1 < value2) ? value1 : value2;
}

template <typename T>
T clamp(T trackValue, T minValue, T maxValue) {
	if (trackValue < minValue) { trackValue = minValue; }
	if (trackValue > maxValue) { trackValue = maxValue; }
	return trackValue;
}


static uint8 UpdateIndex(uint8 &frameDelay, uint8 &frameCounter, uint8 &currentIdx, uint8 frameCount) {
	if (frameCounter % frameDelay == 0) {
		currentIdx = (currentIdx + 1) % frameCount;
	}
	frameCounter++;
	return currentIdx;
}

static void AnimateSprite(Texture2D &baseSprite, Texture2D *animatedSprite, Vector2 pos, uint8 frameCount, uint8 frameDelay, uint8 &idx, Color color) {
	static uint8 frameCounter = 0;
	if (frameCounter % frameDelay == 0) {
		idx = (idx + 1) % frameCount;
	}
	++frameCounter;
	baseSprite = animatedSprite[idx];
	DrawTexture(baseSprite, pos.x, pos.y, color);
}

//static bool AnimateSpriteBool(Texture2D &baseSprite, Texture2D *animatedSprite, Vector2 pos,
//	uint8 frameCount, uint8 frameDelay, uint8 &idx, uint8 &frameCounter) {
//	if (frameCounter % frameDelay == 0) {
//		idx = (idx + 1) % frameCount;
//	}
//	++frameCounter;
//
//	if (idx < 19) {
//		baseSprite = animatedSprite[idx];
//		DrawTexture(baseSprite, pos.x, pos.y, WHITE);
//		return true;
//	}
//	else {
//		idx = 0;
//		return false;
//	}
//}

static float NormalizeVector2(float x, float y) {
	return std::sqrt(x * x + y * y);
}

static int16 GetTextPosX(const char *text, Rectangle rect, uint8 textSize) {
	uint8 textWidth = MeasureText(text, textSize);
	return rect.x + (rect.width - textWidth) / 2;
}

static int16 GetTextPosY(const char *text, Rectangle rect, uint8 textSize) {
	return rect.y + (rect.height / 2) - (textSize / 2);
}


static Color GetMixColor(Color color1, Color color2) {
	return Color(
		(max(0, color1.r + color2.r)),
		(max(0, color1.g + color2.g)),
		(min<unsigned char>(max(color1.b, color2.b), color1.b + color2.b)),
		255
	);
}

static float GetRandomValueFloat(float min, float max) {
	return static_cast<float>(rand()) / (RAND_MAX * (max - min) + min);
}

static float GetRandomValueFloat(int value) {
	return rand() % value;
}

static bool IsCursorOnRect(Vector2 &mousePos, Rectangle rect) {
	return (mousePos.x >= rect.x && mousePos.x < rect.x + rect.width) &&
		(mousePos.y >= rect.y && mousePos.y < rect.y + rect.height);
}

static bool IsClickedOnRect(Vector2 &mousePos, Rectangle rect) {
	return IsCursorOnRect(mousePos, rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}