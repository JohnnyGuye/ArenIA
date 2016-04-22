#pragma once

#include "GUIElement.h"
#include <OGRE\Ogre.h>
#include <OIS\OIS.h>
#include "OgreConsoleForGorilla.h"

class GUIConsole
	: GUIElement
{
public:

	GUIConsole(Ogre::Viewport* vP)
		: GUIElement(vP, "dejavu")
	{
		mConsole = new OgreConsole();
		mConsole->init(screen_);
		mConsole->setVisible(false);
	}

	void setVisible(bool v)	{ mConsole->setVisible(v);	}
	bool isVisible()	{	return mConsole->isVisible();	}

	void print(const Ogre::String &text){ mConsole->print(text);	}

	void onKeyPressed(const OIS::KeyEvent &arg)
	{
		mConsole->onKeyPressed(arg);
	}

	bool frameStarted(const Ogre::FrameEvent &evt)
	{
		return mConsole->frameStarted(evt);
	}

	virtual ~GUIConsole(void)
	{
	}

protected:

	OgreConsole*            mConsole;
	
	Gorilla::Layer*         mFPSLayer;
	Gorilla::Caption*       mFPS;
	Ogre::Real              mTimer;
};

