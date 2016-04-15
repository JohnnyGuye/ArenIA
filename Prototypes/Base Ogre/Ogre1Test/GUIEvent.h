#pragma once

#include <OGRE/Ogre.h>
#include "Gorilla.h"

class GUIEvent
{
public:

	inline GUIEvent(void)
	{
	}

	inline virtual ~GUIEvent(void)
	{
	}

	inline bool init(Ogre::Viewport* vP)
	{
		silverback_ = new Gorilla::Silverback();
		silverback_->loadAtlas("dejavu");
		screen_ = silverback_->createScreen(vP, "dejavu");

		return true;
	}

	Ogre::Real		timer1_, timer2_;
	Gorilla::Silverback*	silverback_;
	Gorilla::Screen*		screen_;
	Gorilla::Layer*			layer_;



};

