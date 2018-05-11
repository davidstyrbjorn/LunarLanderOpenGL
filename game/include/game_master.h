#pragma once

#include"sound.h"

class GameMaster {

private:
	// Static members used across the game
	static bool s_gameOver;
	static bool s_gameWon;
	static int s_Score;

public:
	GameMaster();

	static void landingPerformed();
	static void crashPerformed();

	static bool gameWon();
	static bool gameLost();

	static void reset();
};