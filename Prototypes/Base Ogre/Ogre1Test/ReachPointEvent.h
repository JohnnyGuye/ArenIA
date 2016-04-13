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
* @summary : This class is an event created when a robot reach a point 
* (usefull for tutorial)
*/

#include <OgreVector3.h>

#include "GameEvent.h"

class ReachPointEvent : public GameEvent
{
public:
	ReachPointEvent(const int& robotID, const Ogre::Vector3& position, const GameTime& gt)
		: GameEvent(gt), robotID_(robotID), position_(position)
	{
	}

	virtual ~ReachPointEvent(void){}

	inline virtual int				getRobotID() const {	return robotID_;	}
	inline virtual Ogre::Vector3	getPosition() const {	return position_;	}
	
	inline virtual EventType		getEventType() const {	return REACHED_POINT;	}

	inline friend std::ostream& operator<<( std::ostream &lhs, const ReachPointEvent& rhs)
	{
		lhs << rhs.getTime().getRound() << " - ";
		lhs << "Point reached - " << rhs.position_ << " - " << rhs.robotID_;
		return lhs;
	}

protected:
	int robotID_;
	Ogre::Vector3 position_;
};

