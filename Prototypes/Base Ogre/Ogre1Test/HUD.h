#pragma once

#include "GUIContext.h"
#include "FightManager.h"

class HUD :
	public GUIContext
{
public:
	HUD(Ogre::Viewport* vp, FightManager* fm);
	virtual ~HUD(void);

	virtual void init(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:
	class RobotInf
		: public GUI::Pane
	{
	public:
		RobotInf(Ogre::Vector2 position, Ogre::Vector2 dimension);
		virtual void init(Gorilla::Layer* layer);

		virtual void setRobot(Robot* r);

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

	float			hudScale;

	Gorilla::Layer*			layerHUD_;
	Gorilla::Layer*			layerIco_;
	Gorilla::Layer*			layerInf_;
	Gorilla::Layer*			layerTop_;
	Gorilla::Layer*			layerMenus_;

};

