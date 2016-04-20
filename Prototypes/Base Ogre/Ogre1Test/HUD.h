#pragma once

#include "GUIElement.h"
#include "FightManager.h"

class HUD :
	public GUIElement
{
public:
	HUD(Ogre::Viewport* vp, FightManager* fm);
	virtual ~HUD(void);

	virtual void init(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:
	class RobotInf 
	{
	public:
		RobotInf(void);
		virtual ~RobotInf(void);

		Robot*					robot_;
		Gorilla::Rectangle*		bloc_;
		Gorilla::Rectangle*		ico_;
		Gorilla::Caption*		name_;
		Gorilla::Caption*		speed_;
		Gorilla::Caption*		orientation_;
	};

	FightManager*			fightManager_;

	Gorilla::Layer*			layerHUD_;
	Gorilla::Layer*			layerIco_;
	Gorilla::Layer*			layerInf_;
	std::vector<RobotInf*>	infRobots_;


};

