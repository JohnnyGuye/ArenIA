#pragma once

#include "GUIContext.h"
#include "FightScene.h"

GUIDecompte::GUIDecompte(Ogre::Viewport* vp, FightScene* fs)
	: GUIContext(vp, "dec_all"),
	timer_(0),
	fs_(fs)
{
	this->mouseVisibility(false);
	Ogre::Real vpW = screen_->getWidth(), 
		vpH = screen_->getHeight();
	layer_ = screen_->createLayer(0);
	rect = layer_->createRectangle(0,0, vpW / 4, vpH / 4);
	rect->position(-vpW, -vpH);
}

bool GUIDecompte::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	GUIContext::frameRenderingQueued(evt);
	timer_ += evt.timeSinceLastFrame;

	if(!(fs_->getFightManager()->IsVictory()))
	{
		if(timer_ < 1)
		{
			rect->height(height_ /4);
			rect->width(rect->height());
			rect->background_image("dec_3");
		}
		else if(timer_ < 2)
		{
			rect->height(height_ /4);
			rect->width(rect->height());
			rect->background_image("dec_2");
		}
		else if(timer_ < 3)
		{
			rect->height(height_ /4);
			rect->width(rect->height());
			rect->background_image("dec_1");
		}
		else if(timer_ < 4)
		{
			rect->height(height_ /4);
			rect->width(rect->height()*4);
			rect->background_image("dec_start");
		}

		rect->position((width_ - rect->width()) /2, (height_ - rect->height()) / 2);
		if(timer_ > 4)
		{
			layer_->destroyRectangle(rect);
			timer_ = 0;
			return false;
		}
	}
	else
	{
		rect = layer_->createRectangle((width_- height_)/2, (height_ - height_/3) / 2, height_, height_ /3);
		rect->background_image("logo_Victory");
		return false;
	}
	return true;
}

GUIDecompte::~GUIDecompte(void)
{
}

