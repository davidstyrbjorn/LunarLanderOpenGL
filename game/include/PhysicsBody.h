#pragma once

#include"vector.h"

class PhysicsBody {
private:
	Vector2 m_Pos; 
	Vector2 m_Displacement; 
	int m_CurrentFuel = MAX_FUEL;

	const float GRAVITY = 2.5f; // Gravity constant
	const float UPWARDS_FORCE = 1.75f;
	const float HORIZONTAL_FORCE = 2.5f;
	const int MAX_FUEL = 100;

public:
	PhysicsBody();

	void moveUp();
	void moveSide();
	void update();

	Vector2 getPosition() { return m_Pos; }
	void setPosition(Vector2 a_Pos) { m_Pos = a_Pos; }
	void reset() { m_Displacement = Vector2(0, 0); }
	void setFuel(int a_Value) { m_CurrentFuel = a_Value; }
	int getFuel() { return m_CurrentFuel; }
	const int getMaxFuel() { return MAX_FUEL; }
};