#include"../include/PhysicsBody.h"

#include"../include/input.h"

#include<GLFW\glfw3.h>
#include<iostream>

PhysicsBody::PhysicsBody()
{
	m_Pos = Vector2(0, 0);
	m_Displacement = Vector2(0, 0);
}

void PhysicsBody::update()
{
	// Reset displacement 

	// Affect the lander with gravity force unless we're tryin to go up!
	if (Input::instance()->isKeyDown(GLFW_KEY_W)) {
		if (m_Displacement.y > -UPWARDS_FORCE) {
			m_Displacement.y -= UPWARDS_FORCE*0.05f;
		}
	}
	else {
		if (m_Displacement.y < GRAVITY) {
			m_Displacement.y += GRAVITY*0.01f;
		}
	}
	// Right & Left 
	if (Input::instance()->isKeyDown(GLFW_KEY_D)) {
		if (m_Displacement.x < HORIZONTAL_FORCE) {
			m_Displacement.x += HORIZONTAL_FORCE * 0.01;
		}
	}
	else if (Input::instance()->isKeyDown(GLFW_KEY_A)) {
		if (m_Displacement.x > -HORIZONTAL_FORCE) {
			m_Displacement.x -= HORIZONTAL_FORCE * 0.01f;
		}
	}
	else {
		if (abs(m_Displacement.x) > 0) {
			m_Displacement.x *= 0.999f;
		}
	}

	m_Pos.x += m_Displacement.x;
	m_Pos.y += m_Displacement.y;
}