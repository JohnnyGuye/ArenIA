#pragma once

#include "GUIContext.h"
#include <OIS\OIS.h>
#include <OIS\OISMouse.h>
#include <OIS\OISInputManager.h>
#include "Robot.h"
#include "WasheeRobot.h"
#include "MowerRobot.h"
#include "Terrain.h"

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp> 



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
	public GUIContext
{
public:

	GUILauncher(Ogre::Viewport*);
	~GUILauncher(void);

	void loadAllElements();

	MapObjects * getmapObjects();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
	virtual bool mouseMoved(const OIS::MouseEvent &arg);

	bool stringStartsWith(std::string myString, std::string myStringFragment);
	bool stringEndsWith(std::string myString, std::string myStringFragment);

	Gorilla::Layer*		layerBase_;
	Gorilla::Layer*		layerListArea_;
	Gorilla::Layer*		layerBackground_;
	Gorilla::Layer*		layerTop_;
	Gorilla::Rectangle*	mouse_;

public:
	Ogre::Real	width_, height_;
	GUI::ListArea*				listArea_;
	MapObjects*					mapObjects_;

	std::vector<Robot * >				myRobots_;
	std::vector<Terrain>				myTerrains_;
	std::vector<std::string>			myAIs_;
	
	
};

