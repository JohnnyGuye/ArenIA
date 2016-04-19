#include "GUIShowLogo.h"

const Ogre::Real GUIShowLogo::
	FADE_IN(0.5f), 
	SHOW(1.0f), 
	FADE_OUT(0.5f);

GUIShowLogo::GUIShowLogo(Ogre::Viewport* vp, const Ogre::String &atlas)
	: GUIElement(vp, atlas),
	timer_(0),
	asChanged_(false),
	idx_(0)
{	
	Ogre::Real		width = screen_->getWidth(),
		height = screen_->getHeight();

	layerImg_ = screen_->createLayer(0);
	layerImg_->show();
	rect_ = layerImg_->createRectangle(0, 0, width / 4, width / 4);
	rect_->position((width - rect_->width()) / 2, (height - rect_->height()) / 2);

	logos_.push_back("logo_ArenIA");
}

bool GUIShowLogo::frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
	timer_+= evt.timeSinceLastFrame;
	int fT = (int)floor(timer_);
	switch(fT % 3)
	{
	case 0:
		
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
		layerImg_->setAlphaModifier(fT);
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
	return true;
}

GUIShowLogo::~GUIShowLogo(void)
{
	silverback_->destroyScreen(screen_);
}