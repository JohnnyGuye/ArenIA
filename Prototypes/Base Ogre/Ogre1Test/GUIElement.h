#pragma once

#include <OGRE\OgreFrameListener.h>
#include <vector>

#include "Gorilla.h"

class GUIElement
{
public:
	GUIElement(Ogre::Viewport* vp, const Ogre::String &atlas = "");
	virtual ~GUIElement(void);

	/// Add a child to this GUIElement
	/// @param elmnt, the GUIElement you want as a child
	/// @return a pointer on the child
	GUIElement* addChild(GUIElement* elmnt);

	/// Get the name of the atlas attached to these GUIElements
	Ogre::String getAtlasName() const;

	/// Update the graphics of the GUIElement
	/// @param evt used for time between frames
	/// @return true if updated
	virtual bool frameRenderingQueue(const Ogre::FrameEvent& evt);

protected:
	GUIElement*					root_;
	GUIElement*					parent_;
	std::vector<GUIElement*>	childs_;

	Gorilla::Silverback*		silverback_;
	Gorilla::Screen*			screen_;
};

