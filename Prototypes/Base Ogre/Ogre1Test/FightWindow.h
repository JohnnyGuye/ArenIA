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
	
// ------------------------------------- FightWindow
public:
    FightWindow(void);
    virtual ~FightWindow(void);

	virtual void go(void);

protected:

	virtual bool setup(void);
	virtual void createFrameListener(void);
	virtual void setupResources(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual void changeScene();

	// Handler sur le clavier/souris
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	static bool isShift();
	static bool isAlt();
	static bool isCtrl();

	 // Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    // Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);


	//------------------------------------------Ogre base
	Ogre::Root*				root_;
	Ogre::RenderWindow*		window_;
	Ogre::String			resourcesCfg_;
	Ogre::String			pluginsCfg_;
	Ogre::Math*				math_;

	// Les cadres de debugs sont affichés par Overlays

	Gorilla::Silverback*		silverback_;
    // OgreBites
    OgreBites::InputContext     inputContext_;
    bool                        cursorWasVisible_;	// Was cursor visible before dialog appeared?
    bool                        shutDown_;

    //OIS Input devices
    OIS::InputManager*          inputManager_;
    OIS::Mouse*                 mouse_;
    OIS::Keyboard*              keyboard_;

	static bool					alt_;
	static bool					lctrl_;
	static bool					rctrl_;
	static bool					lshift_;
	static bool					rshift_;

    // Added for Mac compatibility
    Ogre::String                 m_ResourcePath;	//Est-ce qu'on le garde vraiment ? Je suis raciste

#ifdef OGRE_STATIC_LIB
    Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif

	//----------------------------------------Game engine
	typedef std::map<std::string, Scene*>	SceneMap;
	typedef std::pair<std::string, Scene*>		ScenePair;
	SceneMap			sceneMap_;
	Scene*				activScene_;
};

//---------------------------------------------------------------------------
