#pragma once

#include "GUIContext.h"

class FightScene;

class GUIDecompte
	: public GUIContext
{
public:

	GUIDecompte(Ogre::Viewport* vp, FightScene* fs);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual ~GUIDecompte(void);

protected:
	Ogre::Real				timer_;

	Gorilla::Layer*         layer_;
	Gorilla::Rectangle*     rect;
	Gorilla::MarkupText*    markup;

	FightScene*		fs_;
};

