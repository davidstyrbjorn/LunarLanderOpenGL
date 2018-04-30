#pragma once

#include"renderable.h"

// Lunar Lander Obejct
class Lander : public Renderable {

public:
	// Static constants for the lander
	const static float s_Width;
	const static float s_Height;

public:
	Lander();
	~Lander();

	void draw() override;

};