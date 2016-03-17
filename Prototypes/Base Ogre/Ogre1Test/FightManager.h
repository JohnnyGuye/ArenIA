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
* /____/      |___| |__|  \__\ |_______| |__| \__| |___| |___|      \____\ project
* 
* Copyright (c) 2016-2017
*
* @author Johnny Guye
* @summary : This class is a fight manager (you surely already noticed that !).
* All the logic of a fight is hold there. But none of the graphics are shown there.
* This means that it is possible to seperate logic from graphics easily and update
* when ever you want without rendering.
*/

#include "Terrain.h"
#include "GameEvent.h"
#include "EndOfDayVictory.h"
#include "StartSDEvent.h"
#include "VictoryHandler.h"
#include "Gauge.h"
#include "Robot.h"

#include <string>
#include <list>

class FightManager
{
public:
	FightManager(const std::string& mapFileName = "essai1.txt", VictoryHandler* vo = new EndOfDayVictory());
	virtual ~FightManager(void);

	/** @brief Load a new terrain into the fight manager 
	**	@param fileName the name of the new map to load **/
	virtual void loadTerrain(const std::string& fileName);

	/** @brief add a new robot in the fight 
	*	@param robot : the new robot **/
	virtual void addRobot(Robot* robot);
	/** @brief Return the terrain
	*	@return the terrain **/
	virtual Terrain* getTerrain() const;

	/** @brief give a timestamp on the actual round
	*	@return the GameTime of the round **/
	virtual GameTime getTime() const;

	/** @brief add en event to the events list 
	*	@param ge : the event to add **/
	virtual void addEvent(GameEvent* ge);

	/** @brief verify if someone won 
	*	@return true conditions of victory are fullfilled **/
	virtual bool IsVictory() const;

	/** @brief go to the next round **/
	virtual void update();

	/** @brief return the number of rounds since the beginning **/
	virtual double getActualTime() const;

	/** @brief return the number of rounds before the end of a day **/
	virtual double getRemainingTime() const;

	/** @brief reset the fight manager to the first state of the match **/
	virtual void reset();

protected:

	/** A gauge representing a day : at the end of the Gauge the fight enter
	the sudden death mode **/
	Gauge day_;

	/** The object representing the victory **/
	VictoryHandler* victoryHandler_;

	/** The terrain nothing more to say **/
	Terrain *terrain_;

	/** A list of the objects which want to be updated **/
	std::list<GameObject*>	objects_;

	/** A chronological list of the events **/
	std::list<GameEvent*>	events_;

	/** A list of the robots in the fight **/
	std::list<Robot*>	robots_;

	int roundAfterSD_;
};

