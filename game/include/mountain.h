#pragma once

#include"renderable.h"

#include<vector>

class Mountain : public Renderable {
private:
	std::vector<int> m_Points;
	Vector2 m_LandingPadX; // Landing-pad X bounds

	Mountain();
	static Mountain* m_Instance;

public:
	static Mountain *instance();
	void init();
	void reset();
	void lost();

	Vector2 getLandingPadBounds() { return m_LandingPadX; }
	std::vector<int>& getPoints() { return m_Points; }
	void draw() override;
};