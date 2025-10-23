#pragma once

using uint = unsigned int;
using uint8 = unsigned char;

struct int2 {
	int x, y;
	
	int2 operator+(const int2& v) {
		return { x + v.x, y + v.y };
	}
	int2 operator-(const int2& v) {
		return { x - v.x, y - v.y };
	}
	int2 operator*(const int2& v) {
		return { x * v.x, y * v.y };
	}
	int2 operator/(const int2& v) {
		return { x / v.x, y / v.y };
	}
};

inline bool operator==(const int2& a, const int2& b) {
	return a.x == b.x && a.y == b.y;
}

struct color8 {
	uint8 r, g, b;
};

inline color8 blendColors(color8 a, color8 b, uint8 blendFactor) {
	constexpr uint8 colorMax = 255;

	color8 blended = {
		a.r + ((b.r - a.r) * blendFactor) / colorMax,
		a.g + ((b.g - a.g) * blendFactor) / colorMax,
		a.b + ((b.b - a.b) * blendFactor) / colorMax
	};

	return blended;
}

struct color8alpha {
	uint8 r, g, b, a;
};