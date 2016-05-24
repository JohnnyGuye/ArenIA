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
* @summary : This class is an event created when a robot kills another.
* You have informations on the murderer and on the victim. Maybe i'll add
* some informations about how the murder was made.
*/

#include <string>

#include "GameEvent.h"

class RobotKillEvent : public GameEvent
{
public:
	RobotKillEvent(const int& victim, const int& killer, const GameTime& gt)
		: GameEvent(gt), victim_(victim), killer_(killer)
	{
	}

	virtual ~RobotKillEvent(void){}

	virtual int			getKillerId() const	{	return killer_;	}
	virtual int			getVictimId() const	{	return victim_;	}

	virtual EventType	getEventType() const {	return ROBOT_KILL;	}

	inline friend std::ostream& operator<<( std::ostream& lhs, const RobotKillEvent& rhs)
	{
		lhs << rhs.getTime().getRound() << " - ";
		lhs << "Robot kill : " << rhs.killer_ << "slained" << rhs.victim_;
		return lhs;
	}

protected:
	int victim_;
	int killer_;
	
};

