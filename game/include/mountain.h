#pragma once

#include"renderable.h"

#include<vector>

class Mountain : public Renderable {
private:
	std::vector<int> m_Points;

public:
	Mountain();
	~Mountain();

	void draw() override;
};