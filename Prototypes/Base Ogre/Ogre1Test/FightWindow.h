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

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#  include <OIS/OISEvents.h>
#  include <OIS/OISInputManager.h>
#  include <OIS/OISKeyboard.h>
#  include <OIS/OISMouse.h>

#  include <OGRE/SdkTrays.h>
#  include <OGRE/SdkCameraMan.h>
#else
#  include <OISEvents.h>
#  include <OISInputManager.h>
#  include <OISKeyboard.h>
#  include <OISMouse.h>

#  include <SdkTrays.h>
#  include <SdkCameraMan.h>
#endif

#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// D3D10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif
#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  include "OgreStaticPluginLoader.h"
#endif

#include "FightManager.h"
#include "Robot.h"
#include "Log.h"
#include "GUIConsole.h"
#include "GUIDecompte.h"
#include "Scene.h"
#include "FightScene.h"

//---------------------------------------------------------------------------

class FightWindow : 
	public Ogre::FrameListener, 
	public Ogre::WindowEventListener, 
	public OIS::KeyListener, 
	public OIS::MouseListener, 
	public OgreBites::SdkTrayListener
{
//------------------------------------- Inner classes
protected:

	enum RenderState {
		CONSOLE_ON,
		GAME,
		COUNTDOWN
	};
	
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

	virtual void go(void);

protected:

	virtual void createEntity(const std::string& mesh, const Ogre::Vector3& position, const int& scale = 1);
	virtual void createRobot(const std::string& name, const Robot::Type& type, const Robot::Team& team = Robot::NONE, const Ogre::Vector3& position = Ogre::Vector3::ZERO, const int& scale = 1);
	virtual void createRobots(void);

	virtual bool setup(void);
    virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual void createViews(void);
	virtual void setupResources(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	// Handler sur le clavier/souris
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	 // Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    // Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);


	//------------------------------------------Ogre base
	Ogre::Root*				root_;
	Ogre::Camera*			camera_;
	Ogre::SceneManager*		sceneMgr_;
	Ogre::RenderWindow*		window_;
	Ogre::String			resourcesCfg_;
	Ogre::String			pluginsCfg_;
	Ogre::Math*				math_;

	// Les cadres de debugs sont affichés par Overlays

    Ogre::OverlaySystem*        overlaySystem_;	// TODO -> Go CEGUI as fast as possible
	Gorilla::Silverback*		silverback_;
    // OgreBites
    OgreBites::InputContext     inputContext_;
    OgreBites::SdkTrayManager*	trayMgr_;
    OgreBites::SdkCameraMan*    cameraMan_;     	// Basic camera controller
    OgreBites::ParamsPanel*     detailsPanel_;   	// Sample details panel
    bool                        cursorWasVisible_;	// Was cursor visible before dialog appeared?
    bool                        shutDown_;

    //OIS Input devices
    OIS::InputManager*          inputManager_;
    OIS::Mouse*                 mouse_;
    OIS::Keyboard*              keyboard_;

    // Added for Mac compatibility
    Ogre::String                 m_ResourcePath;	//Est-ce qu'on le garde vraiment ? Je suis raciste

#ifdef OGRE_STATIC_LIB
    Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif

	//----------------------------------------Game engine
	typedef std::map<std::string, Scene*>	SceneMap;
	typedef std::pair<std::string, Scene*>		ScenePair;
	SceneMap			sceneMap_;	
	FightManager*		fightManager_;	// The logic of the game 

	std::vector<Ogre::Entity*>	DecorEntities_; // The entities corresponding to the scenery 
	std::list<RobotEntity>		robotsEntities_; // The robots to carry 
	std::list<GameEntity>		objectEntities_;	// The other objects to carry
	Sun*						theSun_;// The sun

	RenderState		state_;
	bool			pause_;
	OgreBites::ParamsPanel*		fightPanel_;
	GUIConsole*		console_;
	GUIDecompte*	decompte_;
	double			displaySpeed_;
	Ogre::Real		lag_;

	
};

//---------------------------------------------------------------------------
