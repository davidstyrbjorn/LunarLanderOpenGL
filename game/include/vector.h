#pragma once

#include<iostream>

struct Vector2 {
	float x, y;

	// Constructor
	Vector2() : x(0), y(0) { }
	Vector2(float _x, float _y) : x(_x), y(_y) { } 

	// Operator
	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}
};


struct Vector3 {
	float x, y, z;
	
	// Constructor
	Vector3() : x(0), y(0), z(0) { }
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
};

struct Vector4 {
	float x, y, z, a;

	// Constructor 
	Vector4() : x(0), y(0), z(0), a(0) { }
	Vector4(float _x, float _y, float _z, float _a) : x(_x), y(_y), z(_z), a(_a) { }
};