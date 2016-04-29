#pragma once

#include "scene.h"
#include "GUICode.h"

class CodeEditScene :
	public Scene
{
public:
	CodeEditScene(void);
	virtual ~CodeEditScene(void);

	virtual	void _loadResources(void);

	virtual bool launch(void);

	virtual void createScene(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual Scenes nextScene() const;

	virtual void destroyScene();

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

protected:
	GUICode*	GUICode_;

};

