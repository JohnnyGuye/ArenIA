#pragma once

#include "GameTime.h"

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
* /____/      |___| |__|  \__\ |_______| |__| \__| |___| |___|      \____\ project
* 
* Copyright (c) 2016-2017
*
* @author Johnny Guye
* @summary : This class represents an event. Wich means that it cannot exist alone.
* Events are created when action occurs. If you need a standard a event representing
* nothing, this class is not abstract for that reason. (But holy shit, why do you
* need a meaningless event ?)
*/

class GameEvent
{

public: 
	enum EventType {
		ROBOT_KILL,
		TEAM_KILL,
		ALL_ROBOTS_KILL,
		NEW_ROBOT_SPAWN,
		ALL_RESSOURCE_COLLECTED,
		REACHED_POINT,
		RESET_TIMER,
		START_SD,
		STANDARD_EVENT
	};

public:
	GameEvent(GameTime time = GameTime())
		: timer_(time)
	{
	}
	virtual ~GameEvent(void){}

	// Override me !
	/** @return the eventtype of your event **/
	inline virtual EventType	getEventType() const
	{
		return STANDARD_EVENT;
	}

	/** @return the time when the event was created **/
	inline virtual GameTime		getTime() const
	{
		return timer_;
	}

	inline friend std::ostream& operator<<( std::ostream &lhs, const GameEvent& rhs)
	{
		lhs << rhs.getTime().getRound() << " - ";
		lhs << "Standard";
		return lhs;
	}

protected:

	/** A timer on the beginning of the action and its duration **/
	GameTime timer_;
	
};

