#pragma once

#include "scene.h"
#include "GUIShowLogo.h"

class LogoScene :
	public Scene
{
public:
	LogoScene(Ogre::RenderWindow* window, Ogre::Root* root);
	virtual ~LogoScene(void);

	virtual bool loadResources(void);
	virtual bool launch(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual Scenes nextScene() const;

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
protected:
	GUIShowLogo*		showLogos_;
	Ogre::Camera*		camera_;
};

