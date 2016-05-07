#pragma once

#include "scene.h"
#include "GUILauncher.h"

class LauncherScene :
	public Scene
{
public:
	LauncherScene(void);
	virtual ~LauncherScene(void);

	virtual bool launch(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual Scenes nextScene() const;

	virtual void destroyScene(void);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

protected:
	virtual void _loadResources(void);

	GUILauncher*		GUILauncher_;
	Ogre::Camera*		camera_;
};

