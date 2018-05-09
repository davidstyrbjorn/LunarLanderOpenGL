#include"../include/game_master.h"

bool GameMaster::s_gameOver = false;
bool GameMaster::s_gameWon = false;

GameMaster::GameMaster()
{

}

void GameMaster::landingPerformed()
{
	s_gameWon = true;
}

void GameMaster::crashPerformed()
{
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