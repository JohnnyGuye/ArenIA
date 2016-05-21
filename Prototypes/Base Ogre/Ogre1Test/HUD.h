#pragma once

#include "GUIContext.h"
#include "FightScene.h"

class FightScene;

class HUD :
	public GUIContext
{
public:
	HUD(Ogre::Viewport* vp, FightScene* fs);
	virtual ~HUD(void);

	virtual void init(void);

	virtual void showMenu(bool show = true);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:
	class ButtonQuit
		: public GUI::Button
	{
	public:
		ButtonQuit(Ogre::Vector2 position, Ogre::Vector2 dimension, FightScene* fs)
			: GUI::Button(position, dimension), fs_(fs)
		{
		}

		virtual ButtonQuit* init(Gorilla::Layer* layer)
		{
			GUI::Button::init(layer);
			this->setBackground("button_back");
			this->setText("Quitter le jeu");
			return this;
		}

		virtual ~ButtonQuit()
		{}

	protected:
		virtual void onClick();

		FightScene* fs_;
	};

	class ButtonBackToMain
		: public GUI::Button
	{
	public:
		ButtonBackToMain(Ogre::Vector2 position, Ogre::Vector2 dimension, FightScene* fs)
			: GUI::Button(position, dimension), fs_(fs)
		{	
		}

		virtual ButtonBackToMain* init(Gorilla::Layer* layer)
		{
			GUI::Button::init(layer);
			this->setBackground("button_back");
			this->setText("Revenir a la selection");
			return this;
		}

		virtual ~ButtonBackToMain()
		{}

	protected:
		virtual void onClick();

		FightScene* fs_;
	};

	class ButtonResume
		: public GUI::Button
	{
	public:
		ButtonResume(Ogre::Vector2 position, Ogre::Vector2 dimension, FightScene* fs)
			: GUI::Button(position, dimension), fs_(fs)
		{	
		}

		virtual ButtonResume* init(Gorilla::Layer* layer)
		{
			GUI::Button::init(layer);
			this->setBackground("button_back");
			this->setText("Reprendre");
			return this;
		}

		virtual ~ButtonResume()
		{}

	protected:
		virtual void onClick();

		FightScene* fs_;
	};

	class RobotInf
		: public GUI::Pane
	{
	public:
		RobotInf(Ogre::Vector2 position, Ogre::Vector2 dimension);
		virtual RobotInf* init(Gorilla::Layer* layer);

		virtual void setRobot(Robot* r);

		virtual bool update(const Ogre::FrameEvent& evt);

		virtual ~RobotInf(void);

		Gorilla::Layer*			layer_;
		Robot*					robot_;
		Gorilla::Rectangle*		ico_;
		Gorilla::Rectangle*		bloc_;
		Gorilla::Rectangle*		gauge_;
		Gorilla::Caption*		name_;
		Gorilla::Caption*		speed_;
		Gorilla::Caption*		orientation_;

		
	};
	FightManager*			fightManager_;
	FightScene*				fightScene_;

	float			hudScale;

	Gorilla::Layer*			layerHUD_;
	Gorilla::Layer*			layerIco_;
	Gorilla::Layer*			layerInf_;
	Gorilla::Layer*			layerTop_;
	Gorilla::Layer*			layerMenus_;

};

