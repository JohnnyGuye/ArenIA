#pragma once

/*
* This source file is a part of the 
*           ______                                  ___   ______
*          /      |                                |   | |      \
*         /       |                                |   | |       \
*        /        |                                |   | |        \
*       /    /|   |  ______     _______   __   __  |   | |   |\    \
*      /    / |   | |      \   |   ____| |  \ |  | |   | |   | \    \
*     /    /__|   | |  |)   |  |  |__    |   \|  | |   | |   |__\    \
*    /    ____    | |      /   |   __|   |       | |   | |    ___     \
*   /    /    |   | |   _  \   |  |      |       | |   | |   |    \    \
*  /    /     |   | |  | \  \  |  |____  |  |\   | |   | |   |     \    \
* /____/      |___| |__|  \__\ |_______| |__| \__| |___| |___|project____\
* 
* Copyright (c) 2016-2017
*
* @author Johnny Guye
* @summary : This class is a is a part of the GUI. 
* It encapsulates the life of screens and take care of getting the instance of
* the silverback. There's no real need to invoke this class as a standalone class.
* In more cases, you have to inherit from this class to create the GUI for the scene.
* The things to know :
* - One GUIElement and the GUIs leaf (and their leaf,...) use one unique atlas, so choose wisely
* - Setting the viewport or the atlas to nothing (or both) means it'll be a child GUI of an other
* - Basically, it's a GUI with no interaction with keyboard and mouse BUT, add the group of 5 :
*   - keyPressed(KeyEvent) / keyReleased (KeyEvent) / 
*   - mouseMoved( MouseEvent ) / mousePressed ( MouseEvent ) / mouseRealesed ( MouseEvent )
*   and call them in their respctive places in the Scene, and it'll catch these events.
* If you destroy a GUIElement, you destroy by the same way, the kidos.
* So if lifetime of the root GUIElement is running out, you are sure that alls kids 
* will soonly be dead too.
*/

#include <OGRE\OgreFrameListener.h>
#include <vector>

#include "Gorilla.h"

class GUIElement
{
public:
	/// Create a new GUIElement. 
	/// It can be use as a root for other GUIElements with the same atlas
	/// @param vp the viewport in wich you want to render the GUI
	/// @param atlas the name of atlas you want to use
	GUIElement(Ogre::Viewport* vp = nullptr, const Ogre::String &atlas = "");

	/// Destroy the GUIElement and its childs if created.
	virtual ~GUIElement(void);

	/// Add a child to this GUIElement
	/// @param elmnt, the GUIElement you want as a child
	/// @return a pointer on the child
	GUIElement* addChild(GUIElement* elmnt);

	/// Get the name of the atlas attached to these GUIElements
	/// @return the atlas name
	Ogre::String getAtlasName() const;

	/// Update the graphics of the GUIElement
	/// @param evt used for time between frames
	/// @return true if updated
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:
	GUIElement*					root_;
	GUIElement*					parent_;
	std::list<GUIElement*>		children_;

	Gorilla::Silverback*		silverback_;
	Gorilla::Screen*			screen_;
};

