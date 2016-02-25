#pragma once

/*
* This source file is a part of the 
*           ______      _______________________     ___   ______
*          /      |   /	        The new         \  |   | |      \
*         /       |  |        Robot fight !      | |   | |       \
*        /        |  |___________________________| |   | |        \
*       /    /|   |  ______     _______   __   __  |   | |   |\    \
*      /    / |   | |      \   |   ____| |  \ |  | |   | |   | \    \
*     /    /__|   | |  |)   |  |  |__    |   \|  | |   | |   |__\    \
*    /    ____    | |      /   |   __|   |       | |   | |    ___     \
*   /    /    |   | |   _  \   |  |      |       | |   | |   |    \    \
*  /    /     |   | |  | \  \  |  |____  |  |\   | |   | |   |     \    \
* /____/      |___| |__|  \__\ |_______| |__| \__| |___| |___|project____\ 
* 
* Copyright (c) 2016-2017
*
* @author Johnny Guye
* @summary : This class is a victory handler. When a whole given team as been slained,
* it grants victory.
*/

#include "victoryhandler.h"
#include "TeamKillEvent.h"

class TeamKillVictory :
	public VictoryHandler
{
public:
	TeamKillVictory(void);
	virtual ~TeamKillVictory(void);

	//Override
	virtual void updateFlags();

	int teamID_;
};

