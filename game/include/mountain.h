#pragma once

#include"renderable.h"

#include<vector>

class Mountain : public Renderable {
private:
	std::vector<Vector2> m_Points;

public:
	Mountain();
	~Mountain();

	void draw() override;
};