#pragma once

#include "Gorilla.h"
#include <OGRE\Ogre.h>
#include <OIS\OIS.h>
#include "OgreConsoleForGorilla.h"

class GUIConsole
{
public:

	GUIConsole(Ogre::Viewport* vP)
	{
		mGorilla = Gorilla::Silverback::getSingletonPtr();
		mGorilla->loadAtlas("dejavu");
		mScreen = mGorilla->createScreen(vP, "dejavu");
   
		mFPSLayer = mScreen->createLayer(14);
		mFPS = mFPSLayer->createCaption(14, 10,10, Ogre::StringUtil::BLANK);

		mConsole = new OgreConsole();
		mConsole->init(mScreen);
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
		delete mGorilla;
	}

protected:

	Gorilla::Silverback*    mGorilla;
	Gorilla::Screen*        mScreen;
	OgreConsole*            mConsole;
	
	Gorilla::Layer*         mFPSLayer;
	Gorilla::Caption*       mFPS;
	Ogre::Real              mTimer;
};

