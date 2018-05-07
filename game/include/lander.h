#pragma once

#include"renderable.h"
#include"PhysicsBody.h"
#include<vector>

// Lunar Lander Obejct
class Lander : public Renderable {

public:
	// Static constants for the lander
	const static float s_Width;
	const static float s_Height;

private:
	std::vector<Vertex> m_LanderVerticesMain;
	std::vector<Vertex> m_LanderVerticesLower;
	PhysicsBody m_PhysicsBody;

public:
	Lander();
	~Lander();

	void draw() override;
	void update();

};