#pragma once

#include"vector.h"

class PhysicsBody {
private:
	Vector2 m_Pos; // s
	Vector2 m_Displacement; // dv
	float m_Acceleration; // da -> x

	const float GRAVITY = 1.0f; // Gravity constant
	const float WEIGHT = 5.0f; // Weight constant ( this feels weird )

public:
	PhysicsBody();

	void update(float dt);

	Vector2 getPosition() { return m_Pos; }
	void setPosition(Vector2 a_Pos) { m_Pos = a_Pos; }
};