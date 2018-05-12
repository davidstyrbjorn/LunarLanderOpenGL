#include"../include/game_master.h"

#include<GLFW\glfw3.h>

#include<string>

bool GameMaster::s_gameOver = false;
bool GameMaster::s_gameWon = false;
int GameMaster::s_Score = 0;

GameMaster::GameMaster()
{

}

void GameMaster::landingPerformed()
{
	if (!s_gameWon) {
		static Sound sound("assets\\landing.wav");
		sound.play();

		s_Score++;
		std::string temp = "Lunar Lander || SCORE: " + std::to_string(s_Score);
		glfwSetWindowTitle(glfwGetCurrentContext(), temp.c_str());
	}
	s_gameWon = true;
}

void GameMaster::crashPerformed()
{
	if (!s_gameOver) {
		static Sound sound("assets\\crashed.wav");
		sound.play();
	}
	s_gameOver = true;
}

bool GameMaster::gameWon()
{
	return s_gameWon;
}

bool GameMaster::gameLost()
{
	return s_gameOver;
}

void GameMaster::reset()
{
	s_gameOver = false;
	s_gameWon = false;
}