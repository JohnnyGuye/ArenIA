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
* @summary : This class is a victory handler. Each time an event occurs in the game,
* you should call handleEvent() and give it in parameters. You can verify if 
* someone won by calling IsVictory(). The classes inherited from this one 
* need to override updateFlags() and the constructor in order to create the 
* good flags and correctly set them when needed.
*/

#include <string>
#include <list>
#include <set>
#include <map>
#include <tuple>

#include "GameEvent.h"
#include "RobotKillEvent.h"

class VictoryHandler
{

	typedef std::map<std::string, bool> FlagsMap;

public:
	VictoryHandler(void);
	virtual ~VictoryHandler(void);

	/** @brief Update the flags **/
	virtual void updateFlags() = 0;	//OVERRIDE ME !

	/** @brief hold the event if usefull for victory 
	*	@return true if usefull **/
	virtual bool handleEvent(GameEvent* ge);
	
	/** @brief Check if the fight reached an end point
	*	@return true if someone won **/
	virtual bool IsVictory() const;

protected:

	/** @brief add a flag **/
	virtual void createFlag(const std::string& attr);

	/** @brief set the state of a flag **/
	virtual void setFlag(const std::string& attr, const bool& state = true);

	/** @brief Number of flags before end **/
	virtual int getFlagsToRaise() const;

protected:

	/** The list of the eventTypes to handle **/
	std::set<GameEvent::EventType> eventsToHandle_;

	/** A list with pointers on all the events needed to change the flags **/
	std::list<GameEvent*> events_;

	/** A map containing the flags needed for a victory **/
	FlagsMap flags_;

	/** Number of flags to raise before victory **/
	int flagsToRaise_;
};

