#pragma once

#include"vector.h"

class PhysicsBody {
private:
	Vector2 m_Pos; 
	Vector2 m_Displacement; 

	const float GRAVITY = 2.5f; // Gravity constant
	const float UPWARDS_FORCE = 1.75f;
	const float HORIZONTAL_FORCE = 2.5f;

public:
	PhysicsBody();

	void moveUp();
	void moveSide();
	void update();

	Vector2 getPosition() { return m_Pos; }
	void setPosition(Vector2 a_Pos) { m_Pos = a_Pos; }
};