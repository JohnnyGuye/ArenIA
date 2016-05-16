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
* - One GUIContext and the GUIs leaf (and their leaf,...) use one unique atlas, so choose wisely
* - Setting the viewport or the atlas to nothing (or both) means it'll be a child GUI of an other
* - Basically, it's a GUI with no interaction with keyboard and mouse BUT, add the group of 5 :
*   - keyPressed(KeyEvent) / keyReleased (KeyEvent) / 
*   - mouseMoved( MouseEvent ) / mousePressed ( MouseEvent ) / mouseRealesed ( MouseEvent )
*   and call them in their respctive places in the Scene, and it'll catch these events.
* If you destroy a GUIContext, you destroy by the same way, the kidos.
* So if lifetime of the root GUIContext is running out, you are sure that alls kids 
* will soonly be dead too.
*/

#include <OGRE\OgreFrameListener.h>
#include <OIS\OISKeyboard.h>
#include <OIS\OISMouse.h>
#include <vector>
#include "Gauge.h"

#include "Gorilla.h"

#pragma warning(disable : 4355)

//------------------------------------------------------------------GUI
namespace GUI
{
	//-------------------------------------------------------------PANE
	class Pane
	{
	public:
		Pane(Ogre::Vector2 position, Ogre::Vector2 dimension = Ogre::Vector2(1.f,1.f));
		
		virtual~Pane();

		virtual void setPosition(Ogre::Vector2 pos);
		virtual void resize(Ogre::Vector2 dimension);
		virtual Ogre::Vector2 getPosition(){	return position_;	}
		virtual Ogre::Vector2 getDimension(){	return dimension_;	}
		virtual bool intersect(Ogre::Vector2 point);

		//Handlers
		virtual bool keyPressed(const OIS::KeyEvent &arg);
		virtual bool keyReleased(const OIS::KeyEvent &arg);
		virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

		//Pane tree
		virtual Pane* getParent()	{		return parent_;		}
		virtual void addChild(Pane* pane)
		{
			childrens_.push_back(pane);
			pane->parent_ = this;
		}

	protected:
		Ogre::Vector2		position_;
		Ogre::Vector2		dimension_;
		Pane*				parent_;
		std::list<Pane*>	childrens_;

		bool dirty_;
		bool initialized_;
	};
	//------------------------------------------------------BUTTON
	class Button
		: public Pane
	{
	public:
		Button(Ogre::Vector2 position, Ogre::Vector2 dimension);
		virtual~Button();
		
		virtual Button* init(Gorilla::Layer*);

		virtual void setBackground(const std::string& sprite_name);
		virtual void setBackground(const Ogre::ColourValue& color);
		virtual void setText(const std::string& text);

		virtual void setPosition(Ogre::Vector2 position);
		virtual void resize(Ogre::Vector2 dimension);

		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	protected:
		virtual void onClick();
		virtual void onRelease();
		
	protected:
		Gorilla::Layer*		layer_;

		Gorilla::Rectangle* back_;
		Gorilla::Caption*	text_;

		bool	clicked_;

	};
	//----------------------------------------------------SLIDEBAR
	class SlideBar
		: public Pane
	{
	public:

		enum Orientation {
			HORIZONTAL, VERTICAL
		};

		SlideBar(Ogre::Vector2 position, Ogre::Vector2 dimension, Orientation orientation = VERTICAL);
		virtual~SlideBar();

		virtual SlideBar* init(Gorilla::Layer*);
		virtual float getCurrent() const;
		virtual void setCurrent(float);
		virtual void regionShown(float ratio);

		virtual void setPosition(Ogre::Vector2 position);
		virtual void resize(Ogre::Vector2 dimension);

		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		virtual bool mouseMoved(const OIS::MouseEvent& arg);

	protected:

		virtual bool moveScroll(Ogre::Real val, bool relative = false);

		Orientation			orientation_;
		Gauge				bar_;
		Gorilla::Layer*		layer_;
		Gorilla::Rectangle*	back_;
		Gorilla::Rectangle*	scroll_;
		Gorilla::Rectangle* arrowTop_;
		Gorilla::Rectangle*	arrowBot_;

		bool clickTop_;
		bool clickBot_;
		bool clickScroll_;
	};
	//----------------------------------------------------LIST
	class List
		: public Pane
	{
	public:

		enum Orientation{
			RIGHT, BOTTOM, LEFT, TOP
		};

		List(Ogre::Vector2 position, Ogre::Vector2 dimension, Orientation orientation = RIGHT);
		virtual~List();

		virtual List* init(Gorilla::Layer* layer);
		virtual int addElement(Pane*);

		virtual void setPosition(Ogre::Vector2 position);
		virtual void resize(Ogre::Vector2 dimension);

	protected:
		SlideBar*		slidebar_;
		Orientation		orientation_;
		Gorilla::Layer*		layer_;
		Gorilla::Rectangle*		back_;
		std::vector<Pane*>		blockList_;
	};

};

//-----------------------------------------------------------------------------
class GUIContext
{
public:
	/// Create a new GUIContext. 
	/// It can be use as a root for other GUIContexts with the same atlas
	/// @param vp the viewport in wich you want to render the GUI
	/// @param atlas the name of atlas you want to use
	GUIContext(Ogre::Viewport* vp = nullptr, const Ogre::String &atlas = "");

	/// Destroy the GUIContext and its childs if created.
	virtual ~GUIContext(void);

	/// Add a child to this GUIContext
	/// @param elmnt, the GUIContext you want as a child
	/// @return a pointer on the child
	GUIContext* addChild(GUIContext* elmnt);

	/// Add a Pane in this context
	/// @param elmnt, the Pane you want to add
	/// @return a pointer on the child
	GUI::Pane* addElement(GUI::Pane*);

	/// Get the name of the atlas attached to these GUIContexts
	/// @return the atlas name
	Ogre::String getAtlasName() const;

	/// Update the graphics of the GUIContext
	/// @param evt used for time between frames
	/// @return true if updated
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);


	//Handlers
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

protected:
	GUIContext*					root_;
	GUIContext*					parent_;
	std::list<GUIContext*>		children_;

	Gorilla::Silverback*		silverback_;
	Gorilla::Screen*			screen_;
	std::list<GUI::Pane*>		panes_;
};

