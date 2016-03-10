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

#include "BaseFightWindow.h"
#include "FightManager.h"

#include <vector>

//---------------------------------------------------------------------------

class FightWindow : public BaseFightWindow
{
public:
    FightWindow(void);
    virtual ~FightWindow(void);

protected:
    virtual void createScene(void);
	virtual void createEntity(const std::string& mesh, const Ogre::Vector3& position, const int& scale);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	class Sun
	{
	public:
		/** Create a sun, be sure note te create two or more Suns, it will cause problems **/
		Sun(FightWindow* fw);
		virtual~Sun();
		void update();
	protected:
		FightWindow* fw_;
		Ogre::SceneManager* sceneMgr_;
		Ogre::Entity* sun_;
		Ogre::Light* light_;
	};

	class GameEntity
	{
	public:
		GameEntity(Ogre::SceneManager* sceneMgr, const std::string& mesh, const Ogre::Vector3& position, const int& scale);
		virtual~GameEntity();
		virtual void update();
	protected:
		Ogre::SceneManager* sceneMgr_;
		Ogre::Entity* entity_;
		Ogre::SceneNode* node_;
		Ogre::AnimationState* animState_;
	};

protected:

	/** The logic of the game **/
	FightManager* fightManager_;

	/** The entities corresponding to the scenery **/
	std::vector<Ogre::Entity*> DecorEntities_;

	/** The sun **/
	Sun* theSun_;

	/** The robots to carry **/
	std::list<GameEntity> robotsEntities_;
};

//---------------------------------------------------------------------------
