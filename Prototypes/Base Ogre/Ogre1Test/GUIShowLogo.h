#pragma once

#include <OGRE\Ogre.h>
#include "Gorilla.h"

class GUIShowLogo
{
public:

	GUIShowLogo(Ogre::Viewport* vp)
		: timer_(0),
		asChanged_(false),
		idx_(0)
	{
		silverback_ = Gorilla::Silverback::getSingletonPtr();
		silverback_->loadAtlas("dec_all");
		
		screen_ = silverback_->createScreen(vp, "dec_all");

		Ogre::Real		width = vp->getWidth(),
			height = vp->getHeight();
		layerImg_ = screen_->createLayer(1);
		rect_ = layerImg_->createRectangle(0, 0, width, height);
		logos_.push_back("logo_ArenIA");
	}

	virtual bool frameRenderingQueue(const Ogre::FrameEvent& evt)
	{
		timer_+= evt.timeSinceLastFrame;
		int fT = floor(timer_);
		switch(fT % 3)
		{
		case 0:
			if(idx_ >= logos_.size())	return false;
			if(!asChanged_)
			{
				rect_->background_image(logos_.at(idx_));
				asChanged_ = true;
			}
			layerImg_->setAlphaModifier(timer_);
			rect_->background_image(logos_.at(fT));
			break;
		case 1:
			layerImg_->setAlphaModifier(1.0);
			break;
		case 2:
		default:
			layerImg_->setAlphaModifier(1 - (timer_ - fT));
			if(asChanged_)
			{
				idx_++;
				asChanged_ = false;
			}
			break;
		}
	}

	virtual ~GUIShowLogo(void)
	{
		silverback_->destroyScreen(screen_);
	}

protected:
	const Ogre::Real	FADE_IN = Ogre::Real(0.5f),
						SHOW = Ogre::Real(1.0f),
						FADE_OUT= Ogre::Real(0.5f);

	std::vector<std::string> logos_;

	Gorilla::Silverback*	silverback_;
	Gorilla::Screen*		screen_;
	Gorilla::Layer*			layerImg_;
	Gorilla::Layer*			layerDark_;
	Gorilla::Rectangle*		rect_;

	Ogre::Real	timer_;
	bool asChanged_;
	int idx_;
};

