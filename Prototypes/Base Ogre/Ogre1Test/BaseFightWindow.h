#pragma once

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

class BaseFightWindow : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, public OgreBites::SdkTrayListener
{
public:
	BaseFightWindow(void);
	virtual ~BaseFightWindow(void);

	virtual void go(void);

protected:
	virtual bool setup(void);
	virtual bool configure(void);
	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createFrameListener(void);
	virtual void createScene(void);
	virtual void destroyScene(void);
	virtual void setupResources(void);
	virtual void loadResources(void);
	virtual void createResourceListener(void);
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

	Ogre::Root*				root_;
	Ogre::Camera*			camera_;
	Ogre::SceneManager*		sceneMgr_;
	Ogre::RenderWindow*		window_;
	Ogre::String			resourcesCfg_;
	Ogre::String			pluginsCfg_;
	Ogre::Math*				math_;

	// Les cadres de debugs sont affichés par Overlays

    Ogre::OverlaySystem*        overlaySystem_;	// TODO -> Go CEGUI as fast as possible

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



};

