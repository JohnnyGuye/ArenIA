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

bool stringStartsWith(std::string myString, std::string myStringFragment);
bool stringEndsWith(std::string myString, std::string myStringFragment);

class LauncherScene;
struct FightInformations;

namespace GUI
{

	//Play Button
	class PlayButton :
		public GUI::Button
	{
	public:
		PlayButton(Ogre::Vector2 position, Ogre::Vector2 dimension, ::LauncherScene* ls);
		virtual~PlayButton();
		void onClick();

	protected:
		::LauncherScene*	ls_;
	};

	//List Area
	class ListArea
		: public GUI::Pane
	{
	public:
		

		ListArea(const Ogre::Vector2& pos, const Ogre::Vector2& dim, LauncherScene*);
		virtual~ListArea();

		ListArea* init(Gorilla::Layer* layer);

		void update();

		virtual void resize(Ogre::Vector2 dimension);

		bool frameRenderingQueued( const Ogre::FrameEvent& evt);

		void loadAllElements();

		void setFightInformationsRobot( Robot *);
		void setFightInformationsAI( std::string *);
		void setFightInformationsTerrain( Terrain *);
		FightInformations * getFightInformations();

	protected:
		Gorilla::Layer*			layerBack_;
		Gorilla::Rectangle*		background_;
		Gorilla::Caption*		cursor_;
		GUI::List*				robotList_;
		GUI::List*				mapList_;
		GUI::List*				AIList_;
		GUI::PlayButton*		playButton_;
		GUI::Button*			areniaLogo_;

		std::vector<Robot*>			myRobots_;
		std::vector<Terrain*>		myTerrains_;
		std::vector<std::string*>	myAIs_;
		LauncherScene*				ls_;

	};

	// Button list
	class ListButton:
		public GUI::Button
	{
	public:
		ListButton(Ogre::Vector2 position, Ogre::Vector2 dimension, LauncherScene*);
		virtual~ListButton();
	protected:
		LauncherScene* ls_;
	};

	//Robot button
	class RobotButton :
		public GUI::ListButton
	{
	public:
		RobotButton(Ogre::Vector2 position, Ogre::Vector2 dimension, LauncherScene*, Robot * robot);
		virtual~RobotButton();
		void onClick();

	protected:

		Robot * robot_;
	};

	//AI Button
	class AIButton :
		public GUI::ListButton
	{
	public:
		AIButton(Ogre::Vector2 position, Ogre::Vector2 dimension,LauncherScene*,  std::string * ai);
		virtual~AIButton();
		void onClick();

	protected:

		std::string * ai_;
	};

	//Terrain Button
	class TerrainButton :
		public GUI::ListButton
	{
	public:
		TerrainButton(Ogre::Vector2 position, Ogre::Vector2 dimension, LauncherScene*,  Terrain * terrain);
		virtual~TerrainButton();
		void onClick();

	protected:

		Terrain * terrain_;
	};



}



// Alors ici, qu'est-ce qu'on a ? Le code du GUI de la fenêtre. C'est un peu le gros gestionnaire.
// Il utilise tout les petits éléments ci dessus qui sont réutilisables sous le namespace GUI
class GUILauncher :
	public GUIContext
{
public:

	GUILauncher(Ogre::Viewport* v, LauncherScene* ls);
	~GUILauncher(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	Gorilla::Layer*		layerBase_;
	Gorilla::Layer*		layerListArea_;
	Gorilla::Layer*		layerBackground_;
	Gorilla::Layer*		layerTop_;
	Gorilla::Rectangle*	mouse_;

public:

	GUI::ListArea*				listArea_;
	LauncherScene* ls_;

	
	
};

