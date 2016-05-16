#pragma once

#include "GUIElement.h"
#include <OIS\OIS.h>
#include <OIS\OISMouse.h>
#include <OIS\OISInputManager.h>
#include "Robot.h"
#include "Terrain.h"
#include <windows.h>
#include <tchar.h> 
#include <strsafe.h>



namespace GUI
{
	class ListArea
		: public GUI::Pane
	{
	public:
		

		ListArea(const Ogre::Vector2& pos, const Ogre::Vector2& dim);
		virtual~ListArea();

		ListArea* init(Gorilla::Layer* layer);

		void update();

		virtual bool intersect(Ogre::Vector2 point);
		virtual void resize(Ogre::Vector2 dimension);

		bool frameRenderingQueued( const Ogre::FrameEvent& evt);

	protected:
		Gorilla::Layer*			layerBack_;
		Gorilla::Rectangle*		background_;
		Gorilla::Caption*		cursor_;
		GUI::List*				robotList_;
		GUI::List*				mapList_;
		GUI::List*				IAList_;
	};
}

typedef struct MapObjects {
	Robot* robot;
	std::string ai;
	Terrain terrain;
} MapObjects;

// Alors ici, qu'est-ce qu'on a ? Le code du GUI de la fenêtre. C'est un peu le gros gestionnaire.
// Il utilise tout les petits éléments ci dessus qui sont réutilisables sous le namespace GUI
class GUILauncher :
	public GUIElement
{
public:

	GUILauncher(Ogre::Viewport*);
	~GUILauncher(void);

	void loadAllElements();

	MapObjects * getmapObjects();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	Gorilla::Layer*		layerBase_;
	Gorilla::Layer*		layerListArea_;
	Gorilla::Layer*		layerBackground_;
	Gorilla::Layer*		layerTop_;
	Gorilla::Rectangle*	mouse_;

public:
	Ogre::Real	width_, height_;
	GUI::ListArea*				listArea_;
	MapObjects*					mapObjects_;
	
};

