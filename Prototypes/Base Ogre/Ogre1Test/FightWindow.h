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
#include "Robot.h"
#include "Log.h"
#include "GUIConsole.h"

#include <vector>

//---------------------------------------------------------------------------

class FightWindow : public BaseFightWindow
{
//------------------------------------- Inner classes
protected:
	
	class Sun
	{
	public:
		/** Create a sun, be sure note te create two or more Suns, it will cause problems **/
		Sun(FightWindow* fw);
		virtual~Sun();
		void update();
	protected:
		FightWindow* fw_;
		Ogre::SceneNode* node_;
		Ogre::SceneManager* sceneMgr_;
		Ogre::Light* light_;

		static const int ORBIT = 100 * Terrain::CELL_SIZE;
		Ogre::Vector2 offset_;
	};

	class GameEntity
	{
	public:
		GameEntity(Ogre::SceneManager* sceneMgr, const std::string& mesh, const Ogre::Vector3& position, const int& scale, GameObject * object = nullptr);
		virtual~GameEntity();
		virtual void update(const Ogre::FrameEvent& evt);
	protected:
		Ogre::SceneManager* sceneMgr_;
		Ogre::Entity* entity_;
		Ogre::Degree orientation_;
		Ogre::SceneNode* node_;
		GameObject* object_;
		Ogre::AnimationState* animState_;
	};

	class RobotEntity : GameEntity
	{
	public:
		RobotEntity(Ogre::SceneManager* sceneMgr, const std::string& mesh, const Ogre::Vector3& position, const int& scale, Robot* robot);
		virtual~RobotEntity();
		virtual void update(const	Ogre::FrameEvent& evt);
		inline virtual std::string stateToString(const Robot::State& state) const;
	protected:
	};

// ------------------------------------- FightWindow
public:
    FightWindow(void);
    virtual ~FightWindow(void);

protected:
    virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual void createEntity(const std::string& mesh, const Ogre::Vector3& position, const int& scale = 1);
	virtual void createRobot(const std::string& name, const Robot::Type& type, const Robot::Team& team = Robot::NONE, const Ogre::Vector3& position = Ogre::Vector3::ZERO, const int& scale = 1);
	virtual void createRobots(void);
	virtual void createViews(void);
	virtual bool FightWindow::setup(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	// Handler sur le clavier/souris
	virtual bool keyPressed(const OIS::KeyEvent &arg);

protected:

	enum RenderState {
		CONSOLE_ON,
		GAME
	};

	FightManager*		fightManager_;	// The logic of the game 

	std::vector<Ogre::Entity*>	DecorEntities_; // The entities corresponding to the scenery 
	std::list<RobotEntity>		robotsEntities_; // The robots to carry 
	std::list<GameEntity>		objectEntities_;	// The other objects to carry
	Sun*						theSun_;// The sun

	RenderState		state_;
	OgreBites::ParamsPanel*		fightPanel_;
	GUIConsole*		console_;
	double			displaySpeed_;
	Ogre::Real		lag_;

	
};

//---------------------------------------------------------------------------
