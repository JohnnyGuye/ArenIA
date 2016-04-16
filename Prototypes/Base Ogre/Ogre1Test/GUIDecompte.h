#pragma once

#include <OGRE/Ogre.h>

#include "Gorilla.h"

class GUIDecompte
{
public:

	inline GUIDecompte(Ogre::Viewport* vP)
		: timer_(0)
	{
		mSilverback = Gorilla::Silverback::getSingletonPtr();
		mSilverback->loadAtlas("dec_all");
		mScreen = mSilverback->createScreen(vP, "dec_all");
		Ogre::Real vpW = mScreen->getWidth(), vpH = mScreen->getHeight();

		mLayer = mScreen->createLayer(0);
		rect = mLayer->createRectangle(0,0, vpW / 8, vpW / 8);

		rect->position(-1000, -1000);
	}

	inline virtual bool frameRenderingQueue(const Ogre::FrameEvent& evt)
	{
		timer_ += evt.timeSinceLastFrame;

		Ogre::Real vpW = mScreen->getWidth(), vpH = mScreen->getHeight();
			if(timer_ < 1)
			{
				rect->background_image("dec_3");
			}
			else if(timer_ < 2)
			{
				rect->background_image("dec_2");
			}
			else if(timer_ < 3)
			{
				rect->background_image("dec_1");
			}
			else if(timer_ < 4)
			{
				rect->background_image("dec_start");
			}

			rect->position(vpW * 7 / 16, vpH * 7 / 16);
			if(timer_ > 4)
			{
				rect->no_background();
				return false;
			}
		return true;
	}

	virtual ~GUIDecompte(void)
	{
		delete mSilverback;
	}

protected:
	Ogre::Real			timer_;
	Gorilla::Silverback*    mSilverback;
	Gorilla::Screen*        mScreen;
	Gorilla::Layer*         mLayer;
	Gorilla::Rectangle*     rect;
	Gorilla::MarkupText*     markup;
};

