#include"../include/PhysicsBody.h"

#include"../include/input.h"

#include<GLFW\glfw3.h>

PhysicsBody::PhysicsBody()
{
	m_Pos = Vector2(0, 0);
	m_Acceleration = Vector2(0, 0);
	m_Displacement = Vector2(0, 0);
}

void PhysicsBody::update()
{
	// Reset displacement 
	m_Displacement = Vector2(0, 0);

	// F = mg;
	// 
	// Affect the lander with gravity force
	float gForce = GRAVITY * WEIGHT;
	m_Displacement.y = gForce;

	if (Input::instance()->isKeyDown(GLFW_KEY_W)) {
		if(abstract.)
	}

	m_Displacement = Vector2(m_Displacement.x + m_Acceleration.x, m_Displacement.y + m_Acceleration.y);

	m_Pos = Vector2(m_Pos.x + m_Displacement.x, m_Pos.y + m_Displacement.y);
}