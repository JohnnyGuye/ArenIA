#pragma once

#include "GUIElement.h"
#include <OIS\OIS.h>
#include <OIS\OISMouse.h>
#include <OIS\OISInputManager.h>

namespace GUI
{
	class Pane
	{
	public:
		Pane()
			: parent_(this)
		{
		}

		virtual void setPosition(Ogre::Vector2 pos)	{	position_ = pos;	}
		virtual void setPosition(Ogre::Real x, Ogre::Real y)	{	position_ = Ogre::Vector2(x, y);	}
		virtual bool intersect(Ogre::Vector2 point) = 0;
		virtual Pane* getParent()	{		return parent_;		}

		virtual void addChild(Pane* pane)
		{
			childrens_.push_back(pane);
			pane->parent_ = this;
		}
	private:
		Ogre::Vector2		position_;
		Pane*				parent_;
		std::list<Pane*>	childrens_;
	};

	class TextArea
	{
	public:
		TextArea(const Ogre::Vector2& pos, const Ogre::Vector2& dim);
		virtual~TextArea();

		void init(Gorilla::Layer* layer);

		int append(const Ogre::String& text = "");
		int newLine(const Ogre::String& text = "");

		void update();

		bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	protected:
		std::list<Ogre::String>		lines_;
		Gorilla::MarkupText*		text_;
		Gorilla::Layer*				layerText_;
		Gorilla::Layer*				layerBack_;
		Gorilla::Rectangle*			background_;
		Gorilla::Rectangle*			cursor_;
		Ogre::Vector2				pos_;
		Ogre::Vector2				dim_;

		bool					dirty_;
		bool					initialised_;
		
	};

	class FlowChartArea
	{
	protected:
		class Bloc;
		class Start;
		class End;
		class Arrow;
	
		/** Low level classes **/
		class Bloc
		{
		public: 
			Bloc(Gorilla::Layer* Layer, Ogre::Vector2 pos, Ogre::Vector2 dim, const Ogre::String& sprite);
			virtual~Bloc();

			virtual bool attach(Arrow* arrow) = 0;
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
		};

		class Arrow
		{
		public:
			Arrow(Gorilla::Layer*);
			virtual~Arrow();

			virtual void setStart(Bloc* start);
			virtual void setEnd(Bloc* end);
		protected:
			Gorilla::Layer*						layer_;
			Gorilla::Rectangle*					head_;
			Gorilla::Polygon*					firstSeg_;
			std::list<Gorilla::Polygon*>		segments_;
			Bloc*	start_;
			Bloc*	end_;
		};

		class Start
			: public Bloc
		{
		public: 
			Start (Gorilla::Layer*, Ogre::Vector2 pos);
			virtual~Start();

			virtual bool attach(Arrow* arrow);
		protected:
			Arrow*		next_;
		};

		class End
			: public Bloc
		{
		public: 
			End (Gorilla::Layer*, Ogre::Vector2 pos);
			virtual~End();

			virtual bool attach(Arrow* arrow);
		protected:
			Arrow*		previous_;
		};
		/** High level class **/
	public:
		FlowChartArea(const Ogre::Vector2& pos, const Ogre::Vector2& dim);
		virtual~FlowChartArea();

		void init(Gorilla::Layer* layer);

		void update();

		virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

		bool frameRenderingQueued( const Ogre::FrameEvent& evt);

	protected:
		Gorilla::Layer*			layerBack_;
		Gorilla::Rectangle*		background_;
		Gorilla::Caption*			cursor_;
		std::list<Bloc*>			blocs_;
		std::list<Arrow*>			arrows_;
		Ogre::Vector2				pos_;
		Ogre::Vector2				dim_;

		bool					dirty_;
		bool initialised_;
	};
}

// Alors ici, qu'est-ce qu'on a ? Le code du GUI de la fenêtre. C'est un peu le gros gestionnaire.
// Il utilise tout les petits éléments ci dessus qui sont réutilisables sous le namespace GUI
class GUICode :
	public GUIElement
{
public:
	GUICode(Ogre::Viewport*);
	~GUICode(void);

	bool GUICode::loadFile(const Ogre::String& fileName);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	Ogre::Real			width_,
						height_;
	Gorilla::Layer*		layerBase_;
	Gorilla::Layer*		layerFlowChart_;
	Gorilla::Layer*		layerBackground_;
	Gorilla::Layer*		layerTop_;
	Gorilla::Rectangle*	mouse_;

	GUI::TextArea*			textArea_;
	GUI::FlowChartArea*		flowChartArea_;
};

