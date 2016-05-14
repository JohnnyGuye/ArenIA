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
* @summary : This class represent a basic Scene
* It's an abstract class and needs to bequeath to reals scenes.
* For the use : 
* 1 - Create it -> LogoScene(...);
* 2 - Load their resources -> loadResources();
* 3 - Launch the scene -> launch();
* 4 - render it -> frameRenderingQueued(...);
* 4bis - Don't forget to assign keys and mouse handlers
*  _  _  _
* /!\/!\/!\ : DON'T OVERRIDE loadResources(void) !!!
* only override the protected version _loadResources(void) (with the underscore)
*/

#include <OGRE\Ogre.h>
#include <OIS\OISEvents.h>
#include <OIS\OISKeyboard.h>
#include <OIS\OISMouse.h>
#include "Gorilla.h"

class Scene
{
public:

	enum Scenes {
		LAUNCHER,
		LOGO,
		CODE,
		FIGHT,
		EXIT
	};

	enum ResourceState {
		NOT_LOADED,
		LOADING,
		LOADED
	};

	/// Create a new scene
	/// A scene is a full
	Scene(void);
	virtual ~Scene(void);

	/// @brief Load the resources needed for the scene in an other thread
	/// Do not override it !
	/// But you have to override the one with the underscore
	virtual void loadResources(void);//c++11 final

	/// Initialize the scene, will cause problems if called before loadResources
	/// @return true if launched, false if failed
	virtual bool launch(void) = 0;

	/// Render a frame of the scene
	/// @param evt, a frameEvent for time elapsed 
	/// @return true if rendering needs to carry on, false if next frame is for an other scene
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;

	/// The nextScene this scene wants after her.
	/// @return The next scene to be loaded, 
	/// or the call to EXIT wich means it is the end of the app
	virtual Scenes nextScene() const = 0;

	/// Cleanup the scene before the next relaunch. But since the scene 
	/// has not been fully deleted, you can keep some informations and the resources.
	virtual void destroyScene() = 0;


//-------------------------------------------------------------------Handlers
	/// Things to do when a key is pressed
	/// @param arg the key pressed
	/// @return i don't get it atm
	virtual bool keyPressed(const OIS::KeyEvent &arg) = 0;

	/// Things to do when a key is released
	/// @param arg the key released
	/// @return i don't get it atm
	virtual bool keyReleased(const OIS::KeyEvent &arg) = 0;

	/// Things to do when the mouse is moved
	/// @param arg the mouse is moved
	/// @return i don't get it atm
    virtual bool mouseMoved(const OIS::MouseEvent &arg) = 0;

	/// Things to do when a mouse button is pressed
	/// @param arg the button pressed
	/// @return i don't get it atm
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

	/// Things to do when a mouse button is released
	/// @param arg the key released
	/// @return i don't get it atm
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

protected:

	/// OVERRIDE ME !!
	/// Place the resources you wanna load. It's encapsulated by @loadResources
	/// And thus, in order to provide a secure use of thread
	virtual void _loadResources(void) = 0;

	/// Getter on the scene manager used to render the scene
	/// @return a ptr on the SceneManager of this scene
	Ogre::SceneManager*		getSceneManager(void) const;

protected:
	ResourceState			resourcesState_;
	Ogre::RenderWindow*		window_;
	Ogre::Root*				root_;
	Ogre::SceneManager*		sceneMgr_;
	Gorilla::Silverback*	silverback_;
	Ogre::Camera*			camera_;

	bool					stop_;
	bool					shutDown_;
};

