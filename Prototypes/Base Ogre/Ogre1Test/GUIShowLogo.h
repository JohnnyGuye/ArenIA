#pragma once

#include "GUIElement.h"

class GUIShowLogo
	: public GUIElement
{
public:

	GUIShowLogo(Ogre::Viewport* vp, const Ogre::String &atlas);
	virtual ~GUIShowLogo(void);
	
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:
	static const Ogre::Real FADE_IN, SHOW, FADE_OUT;

	std::vector<std::string> logos_;

	Gorilla::Layer*			layerImg_;
	Gorilla::Rectangle*		rect_;

	Ogre::Real	timer_;
	bool asChanged_;
	unsigned int idx_;
};

