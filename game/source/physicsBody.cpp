#include"../include/PhysicsBody.h"

PhysicsBody::PhysicsBody()
{
	m_Pos = Vector2(0, 0);
	m_Acceleration = 0;
	m_Displacement = Vector2(0, 0);
}

void PhysicsBody::update(float dt)
{
	// Reset displacement 
	m_Displacement = Vector2(0, 0);

	// F = mg;
	// 
	// Affect the lander with gravity force
	float gForce = GRAVITY * WEIGHT;
	m_Displacement.y = gForce;

	m_Pos = Vector2(m_Pos.x + m_Displacement.x * dt, m_Pos.y + m_Displacement.y * dt);
}