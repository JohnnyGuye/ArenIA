#include "GUIShowLogo.h"

const Ogre::Real GUIShowLogo::FADE_IN(1.0f);
const Ogre::Real GUIShowLogo::SHOW(2.0f);
const Ogre::Real GUIShowLogo::FADE_OUT(1.0f);
const Ogre::Real GUIShowLogo::FULL_FRAME(GUIShowLogo::FADE_IN + GUIShowLogo::FADE_OUT + GUIShowLogo::SHOW);

GUIShowLogo::GUIShowLogo(Ogre::Viewport* vp)
	: GUIContext(vp, "logo"),
	lowTimer_(0),
	asChanged_(false),
	idx_(0)
{	
	Ogre::Real		width = screen_->getWidth(),
		height = screen_->getHeight();

	layerImg_ = screen_->createLayer(0);
	layerImg_->show();
	rect_ = layerImg_->createRectangle(0, 0, width / 2, width / 2);
	rect_->position((width - rect_->width()) / 2, (height - rect_->height()) / 2);

	logos_.push_back("ogre");
	logos_.push_back("arenia");
	logos_.push_back("ogre");
}

bool GUIShowLogo::frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
	lowTimer_ += evt.timeSinceLastFrame;
	while(lowTimer_ > FULL_FRAME)	lowTimer_-= FULL_FRAME;
	if(lowTimer_ < FADE_IN)//FADE_IN
	{
		if(!asChanged_)
		{
			if(idx_ < logos_.size())
			{
				rect_->background_image(logos_.at(idx_));
				asChanged_ = true;
			}
			else
			{
				rect_->no_background();
				return false;
			}
		}
		layerImg_->setAlphaModifier(lowTimer_ / FADE_IN);
	}
	else if( lowTimer_ < FADE_IN + SHOW)//EXPOSITION
	{
		layerImg_->setAlphaModifier(1.0f);
	}
	else if(lowTimer_ < FULL_FRAME)//FADE_OUT
	{
		if(asChanged_)
		{
			idx_++;
			asChanged_ = false;
		}
		layerImg_->setAlphaModifier((FULL_FRAME - lowTimer_) / FADE_OUT);
	}
	return true;
}

GUIShowLogo::~GUIShowLogo(void)
{
}