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