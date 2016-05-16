#pragma once

#include "GUIElement.h"

class GUIDecompte
	: public GUIContext
{
public:

	inline GUIDecompte(Ogre::Viewport* vp, const Ogre::String &atlas)
		: GUIContext(vp, atlas),
		timer_(0)
	{
		Ogre::Real vpW = screen_->getWidth(), 
			vpH = screen_->getHeight();

		layer_ = screen_->createLayer(0);
		rect = layer_->createRectangle(0,0, vpW / 4, vpH / 4);

		rect->position(-vpW, -vpH);
	}

	inline virtual bool frameRenderingQueue(const Ogre::FrameEvent& evt)
	{
		timer_ += evt.timeSinceLastFrame;

		Ogre::Real vpW = screen_->getWidth(), 
			vpH = screen_->getHeight();
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

			rect->position(vpW * 3 / 8, vpH * 3 / 8);
			if(timer_ > 4)
			{
				layer_->setAlphaModifier(0);
				rect->no_background();
				return false;
			}
		return true;
	}

	virtual ~GUIDecompte(void)
	{
	}

protected:
	Ogre::Real				timer_;

	Gorilla::Layer*         layer_;
	Gorilla::Rectangle*     rect;
	Gorilla::MarkupText*    markup;
};

