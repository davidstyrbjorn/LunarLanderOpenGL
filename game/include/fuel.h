#pragma once

#include"renderable.h"
#include"PhysicsBody.h"

class FuelBar : public Renderable {
private:
	PhysicsBody& m_LanderBody;

public:
	FuelBar(PhysicsBody& a_LanderBody);
	~FuelBar();

	void draw() override;
};