#pragma once

#include"vector.h"
#include"config.h"

#include<stdlib.h>
#include<time.h>
#include<vector>

static bool landscapeCreated = false;
static std::vector<int> staticLandscape = { };

static float random() {
	float x = rand() / (float)RAND_MAX;
	return x;
}

static std::vector<int> getLandscape()
{
	srand(time(NULL));
	std::vector<int> points;

	// Algorithm parameters
	auto STEP_MAX = 0.9f;
	auto STEP_CHANGE = 0.2f;
	auto HEIGHT_MAX = HEIGHT*0.6f;

	// Initial conditions
	auto height = random() * HEIGHT_MAX;
	auto slope = (random()*STEP_MAX) * 2 - STEP_MAX;

	// Iterate to create landscape values
	for (int i = 0; i < WIDTH; i++) {
		// Change height and slope
		height += slope;
		slope += (random() * STEP_CHANGE) * 2 - STEP_CHANGE;

		// Clamp height and slope
		if (slope > STEP_MAX) { slope = STEP_MAX; }
		if (slope < -STEP_MAX) { slope = -STEP_MAX; }
		if (height > HEIGHT_MAX) {
			height = HEIGHT_MAX;
			slope *= -1;
		}
		if (height < 0) {
			height = 0;
			slope *= -1;
		}

		points.push_back(height);
	}

	return points;
}

static std::vector<int> getStaticLandscape()
{
	if (landscapeCreated == false) {
		staticLandscape = getLandscape();
		landscapeCreated = true;
	}
	return staticLandscape;
}