#pragma once

#include "GUIElement.h"
#include <OIS\OIS.h>
#include <OIS\OISMouse.h>
#include <OIS\OISInputManager.h>
#include "Robot.h"
#include "Terrain.h"
//#include <boost/filesystem.hpp>



namespace GUI
{
	class ListArea
	{
	protected:
		class Block;
		class BlockList;

		enum blockTypes {
		ROBOT,
		AI,
		MAP
		};
	
		/** Low level classes **/
		class Block
		{
		public: 
			Block(Gorilla::Layer* Layer, Ogre::Vector2 pos, Ogre::Vector2 dim, const Ogre::String& sprite, blockTypes blockType);
			virtual~Block();

			virtual bool mouseMoved(const OIS::MouseEvent &arg);
			virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
			virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

		protected:
			
			Gorilla::Layer*		layer_;
			Gorilla::Rectangle*	rect_;

			/** Interaction part **/
			Gorilla::Polygon*	hitBox_;
			Ogre::Vector2		topLeftDist_;
			bool				onHold_;
			blockTypes			blockType_;
		};

		class RobotBlock
			: public Block
		{
			public:
			RobotBlock( Gorilla::Layer*, Ogre::Vector2, Robot* );
			virtual~RobotBlock();
			Robot* getRobot();

			protected:
				Robot* robot_;

		};

		class BlockList
		{
		public: 
			BlockList(Gorilla::Layer* Layer, Ogre::Vector2 pos, Ogre::Vector2 dim, const Ogre::String& sprite, blockTypes blockType);
			BlockList();
			virtual~BlockList();

			std::list<Block*> getBlocks();

			virtual bool mouseMoved(const OIS::MouseEvent &arg);
			virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
			virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

		protected:
			
			Gorilla::Layer*		layer_;
			Gorilla::Rectangle*	rect_;
			Gorilla::Polygon*	hitBox_;
			std::list<Block*>	blocks_;
			blockTypes			blockType_;

			/*
			Gorilla::Polygon*	hitBox_;
			Ogre::Vector2		topLeftDist_;
			bool				onHold_; */
			
			
		};


		/** High level class **/
	public:
		

		ListArea(const Ogre::Vector2& pos, const Ogre::Vector2& dim);
		virtual~ListArea();

		void init(Gorilla::Layer* layer);

		void update();

		virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

		bool frameRenderingQueued( const Ogre::FrameEvent& evt);

	protected:
		Gorilla::Layer*			layerBack_;
		Gorilla::Rectangle*		background_;
		Gorilla::Caption*		cursor_;
		BlockList				robotList_;
		BlockList				aiList_;
		BlockList				mapList_;
		Ogre::Vector2			pos_;
		Ogre::Vector2			dim_;

		bool						dirty_;
		bool						initialised_;
	};
}

typedef struct mapObjects {
	Robot robot;
	std::string ai;
	Terrain terrain;
} mapObjects;

// Alors ici, qu'est-ce qu'on a ? Le code du GUI de la fenêtre. C'est un peu le gros gestionnaire.
// Il utilise tout les petits éléments ci dessus qui sont réutilisables sous le namespace GUI
class GUILauncher :
	public GUIElement
{
public:

	GUILauncher(Ogre::Viewport*);
	~GUILauncher(void);

	bool GUILauncher::loadFile(const Ogre::String& fileName);
	bool stringHasEnding(std::string &myString, std::string const &ending);
	bool stringHasBeginning(std::string &myString, std::string const &beginning);
	void loadAllElements();


	mapObjects * getmapObjects();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	Ogre::Real			width_,
						height_;
	Gorilla::Layer*		layerBase_;
	Gorilla::Layer*		layerListArea_;
	Gorilla::Layer*		layerBackground_;
	Gorilla::Layer*		layerTop_;
	Gorilla::Rectangle*	mouse_;

public:
	static std::list<Robot>			robots_;
	std::list<Ogre::String>		ais_;
	std::list<Terrain>			maps_;
	GUI::ListArea*				listArea_;
	mapObjects*					mapObjects_;
	
};

