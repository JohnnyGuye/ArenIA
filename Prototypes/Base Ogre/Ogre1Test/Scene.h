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
* 3 - Launch the scene -> lunch();
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
		LOGO,
		FIGHT,
		EXIT
	};

	enum ResourceState {
		NOT_LOADED,
		LOADING,
		LOADED
	};

	Scene(Ogre::RenderWindow* window, Ogre::Root* root);
	virtual ~Scene(void);

	/// Do not override it !
	virtual void loadResources(void);
	virtual bool launch(void) = 0;
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;
	virtual Scenes nextScene() const = 0;
	virtual void destroyScene();

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

	Ogre::SceneManager*		getSceneManager(void) const;

protected:
	ResourceState			resourcesState_;
	Ogre::RenderWindow*		window_;
	Ogre::Root*				root_;
	Ogre::SceneManager*		sceneMgr_;
	Gorilla::Silverback*	silverback_;
};

