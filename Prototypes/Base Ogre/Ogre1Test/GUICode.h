#pragma once

#include "GUIElement.h"

class GUICode :
	public GUIElement
{
public:
	GUICode(Ogre::Viewport*);
	~GUICode(void);

	bool GUICode::loadFile(const Ogre::String& fileName);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	Ogre::Real			width_,
						height_;
	Gorilla::Layer*		layerBase_;
	Gorilla::Layer*		layerBackground_;
	Gorilla::Layer*		layerTop_;

	Gorilla::MarkupText*	codeArea_;
};

