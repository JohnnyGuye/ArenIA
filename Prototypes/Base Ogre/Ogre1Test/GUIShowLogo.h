#pragma once

#include "GUIElement.h"

class GUIShowLogo
	: public GUIElement
{
public:

	GUIShowLogo(Ogre::Viewport* vp);
	virtual ~GUIShowLogo(void);
	
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:
	static const Ogre::Real FADE_IN, SHOW, FADE_OUT, FULL_FRAME;

	std::vector<std::string> logos_;

	Gorilla::Layer*			layerImg_;
	Gorilla::Rectangle*		rect_;

	Ogre::Real	lowTimer_;
	bool asChanged_;
	unsigned int idx_;
};

