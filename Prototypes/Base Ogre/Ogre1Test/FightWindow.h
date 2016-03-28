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

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <vector>

//---------------------------------------------------------------------------

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

//---------------------------------------------------------------------------

class FightWindow : public BaseFightWindow
{
public:
    FightWindow(void);
    virtual ~FightWindow(void);

protected:
	virtual void setupResources(void);
    virtual void createScene(void);
	virtual void createEntity(const std::string& mesh, const Ogre::Vector3& position, const int& scale);
	virtual void createRobot(const std::string& mesg, const Ogre::Vector3& position, const int& scale, Robot* robot);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createFrameListener(void);
	virtual void loadResources(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	/** Events **/
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

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
	protected:
	};

protected:

	/** The logic of the game **/
	FightManager*				fightManager_;

	/** The entities corresponding to the scenery **/
	std::vector<Ogre::Entity*>	DecorEntities_;

	/** The sun **/
	Sun*						theSun_;

	/** The robots to carry **/
	std::list<RobotEntity>		robotsEntities_;

	/** The other objects to carry **/
	std::list<GameEntity>		objectEntities_;

	/** The CEGUI renderer **/
	CEGUI::OgreRenderer*		renderer_;
};

//---------------------------------------------------------------------------
