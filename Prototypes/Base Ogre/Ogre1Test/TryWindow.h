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
* @summary : This class show the game
*/

#include "FightWindow.h"
#include "FightManager.h"

#include <vector>

//---------------------------------------------------------------------------

class TryWindow : public FightWindow
{
public:
    TryWindow(void);
    virtual ~TryWindow(void);

protected:
    virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:

	/** The logic of the game **/
	FightManager* fightManager_;

	/** The entities corresponding to the scenery **/
	std::vector<Ogre::Entity*> DecorEntities;

	/** The sun **/
	Ogre::Light* sunLight;
	Ogre::Entity* sunEntity;
};

//---------------------------------------------------------------------------
