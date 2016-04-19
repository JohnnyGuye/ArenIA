#pragma once

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
	Scene(Ogre::RenderWindow* window, Ogre::Root* root);
	virtual ~Scene(void);

	virtual bool loadResources(void) = 0;
	virtual bool launch(void) = 0;
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;
	virtual Scenes nextScene() const = 0;

	virtual bool keyPressed(const OIS::KeyEvent &arg) = 0;
	virtual bool keyReleased(const OIS::KeyEvent &arg) = 0;
    virtual bool mouseMoved(const OIS::MouseEvent &arg) = 0;
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

	Ogre::SceneManager*		getSceneManager(void) const;

protected:
	Ogre::RenderWindow*		window_;
	Ogre::Root*				root_;
	Ogre::SceneManager*		sceneMgr_;
	Gorilla::Silverback*	silverback_;
};

