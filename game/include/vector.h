#pragma once

struct Vector2 {
	float x, y;

	// Constructor
	Vector2(float _x, float _y) : x(_x), y(_y) { } 
};


struct Vector3 {
	float x, y, z;
	
	// Constructor
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
};

struct Vector4 {
	float x, y, z, a;

	// Constructor 
	Vector4(float _x, float _y, float _z, float _a) : x(_x), y(_y), z(_z), a(_a) { }
};