#pragma once

#include"vector.h"

class PhysicsBody {
private:
	Vector2 m_Pos; // s
	Vector2 m_Displacement; // dv
	Vector2 m_Acceleration; // da -> x

	const float GRAVITY = 0.5f; // Gravity constant
	const float WEIGHT = 5.0f; // Weight constant ( this feels weird )

public:
	PhysicsBody();

	void update();

	Vector2 getPosition() { return m_Pos; }
	void setPosition(Vector2 a_Pos) { m_Pos = a_Pos; }
};