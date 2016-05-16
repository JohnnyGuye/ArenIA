#include "HUD.h"

using namespace Gorilla;
using namespace Ogre;

HUD::HUD(Viewport* vp, FightManager* fm)
	: GUIContext(vp, "HUD"),
	fightManager_(fm),
	width_(screen_->getWidth()),
	height_(screen_->getHeight()),
	hudScale(0.070f)
{
	this->mouseVisibility(false);
	layerHUD_ = screen_->createLayer(10);
	layerIco_ = screen_->createLayer(9);
	layerInf_ = screen_->createLayer(11);
	layerTop_ = screen_->createLayer(12);
}

HUD::~HUD(void)
{
	for(unsigned int i = 0; i < infRobots_.size() ; i++)
	{
		delete infRobots_[i];
	}
}

void HUD::init(void)
{
	Vector2 hudPosition(0.005f, 0.03f);
	float dist = 0.010f;
	Vector2 hudRatio (2.855f, 1);
	Vector2 icoPosition(0.005f, 0.03f);
	Vector2 namePos(0.100f, 0.03f);
	Vector2 infPos(0.080f, 0.060f);
	Vector2 gaugePos(0.175f, 0.03f);
	Vector2 gaugeRatio(0.25f, 1);

	//---Robots
	std::list<Robot*> robots = fightManager_->getRobots();
	int i = 0;
	for(std::list<Robot*>::iterator it = robots.begin(); it!= robots.end(); it++)
	{
		Robot* robot = (*it);
		RobotInf* ri = new RobotInf();
		ri->robot_ = robot;

		//Setting background robotinformation
		ri->bloc_ = layerHUD_->createRectangle(hudPosition * width_, hudRatio * width_ * hudScale);
		ri->bloc_->background_image("robothud");
		ri->bloc_->top(ri->bloc_->top() + i * (hudScale + dist) * width_);

		//Setting icone for a robot
		ri->ico_ = layerIco_->createRectangle(icoPosition * width_, Vector2(1,1) * width_ * hudScale);
		ri->ico_->background_image("ico_tondeuse");
		ri->ico_->top(ri->ico_->top() + i * (hudScale + dist) * width_);

		//Setting the name
		ri->name_ = layerInf_->createCaption(14, 
			namePos.x * width_, 
			(namePos.y + i * (hudScale + dist)) * width_, 
			robot->getName());

		//Setting the speed
		std::stringstream so;
		std::stringstream ss;
		ss << robot->getFullStats().hp.getCurrent();
		ri->speed_ = layerInf_->createCaption(9, 
			infPos.x * width_, 
			(infPos.y + i * (hudScale + dist)) * width_, 
			ss.str());

		//Setting the orientation
		so << robot->getOrientation().valueDegrees() << "'";
		ri->orientation_ = layerInf_->createCaption(9, 
			infPos.x * width_, 
			(infPos.y + dist + i * (hudScale + dist)) * width_, 
			so.str());

		//Setting life/energy
		ri->gauge_ = layerTop_->createRectangle(gaugePos.x * width_, 
			(gaugePos.y + i * (hudScale + dist)) * width_,
			gaugeRatio.x * hudScale * width_, gaugeRatio.y * hudScale * width_);
		ri->gauge_->background_image("gauges_sepia");
		infRobots_.push_back(ri);
		i++;

	}

	//---Events
	
	
}

bool HUD::frameRenderingQueued(FrameEvent const& evt)
{
	for(std::vector<RobotInf*>::iterator it = infRobots_.begin(); it != infRobots_.end();it++)
	{
		std::stringstream so;
		std::stringstream ss;
		so << (*it)->robot_->getOrientation().valueDegrees() << "'";
		(*it)->orientation_->text(so.str());

		ss.flush();
		ss << (*it)->robot_->getFullStats().hp.getCurrent();
		(*it)->speed_->text(ss.str());
	}
	return true;
}

HUD::RobotInf::RobotInf(void)
	: bloc_(nullptr)
{
}

HUD::RobotInf::~RobotInf(void)
{
}