#pragma once

/*
* This source file is a part of the 
*           ______                                  ___   ______
*          /      |                                |   | |      \
*         /       |                                |   | |       \
*        /        |                                |   | |        \
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
* @summary : This class is an event created a whole team is erased from the
* surface of the world
*/

#include "GameEvent.h"

class TeamKillEvent :
	public GameEvent
{
public:

	TeamKillEvent(const int& team, const GameTime& gt)
		: GameEvent(gt), team_(team)
	{
	}

	virtual ~TeamKillEvent(void)
	{
	}

	inline virtual int			getTeamId() const {		return team_;	}

	inline virtual EventType	getEventType() const {	return TEAM_KILL;	}

	inline friend std::ostream& operator<<( std::ostream& lhs, const TeamKillEvent& rhs)
	{
		lhs << rhs.getTime().getRound() << " - ";
		lhs << "Team eradication : " << rhs.team_ << " is not anymore a team";
		return lhs;
	}

protected:
	int team_;
};

