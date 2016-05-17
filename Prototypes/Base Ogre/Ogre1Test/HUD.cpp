#include "HUD.h"

using namespace Gorilla;
using namespace Ogre;

HUD::HUD(Viewport* vp, FightManager* fm)
	: GUIContext(vp, "HUD"),
	fightManager_(fm),
	hudScale(0.070f)
{
	this->mouseVisibility(false);
	layerIco_ = screen_->createLayer(9);
	layerHUD_ = screen_->createLayer(10);
	layerInf_ = screen_->createLayer(11);
	layerTop_ = screen_->createLayer(12);
	layerMenus_ = screen_->createLayer(13);
}

HUD::~HUD(void)
{
}

void HUD::init(void)
{
	Vector2 hp(0.005f, 0.03f);
	float dist = 0.15f;
	Vector2 ratio (2.855f, 1);

	//---Robots
	std::list<Robot*> robots = fightManager_->getRobots();
	int i = 0;
	for(std::list<Robot*>::iterator it = robots.begin(); it!= robots.end(); it++)
	{

		RobotInf* ri = new RobotInf(Ogre::Vector2(hp.x * width_, (hp.y + dist * i) * height_), ratio * width_ * hudScale);
		ri->init(layerMenus_);
		ri->setRobot(*it);

		addElement(ri);
		i++;

	}

	//---Events
	
	
}

bool HUD::frameRenderingQueued(FrameEvent const& evt)
{
	return true;
}

HUD::RobotInf::RobotInf(Ogre::Vector2 position, Ogre::Vector2 dimension)
	: Pane(position, dimension)
{
}

void HUD::RobotInf::init(Gorilla::Layer* layer)
{
	layer_ = layer;
	ico_ = layer_->createRectangle(position_.x, position_.y, dimension_.y, dimension_.y);

	bloc_ = layer_->createRectangle(position_, dimension_);
	bloc_->background_image("robothud");

	name_ = layer->createCaption(14, (position_.x + dimension_.x) / 2, position_.y, "");
	name_->align(Gorilla::TextAlign_Centre);

	speed_ = layer->createCaption(9, position_.x + 2.f/5.f * dimension_.x,
		position_.y + 2.f/5.f * dimension_.y, "");

	orientation_ = layer->createCaption(9, position_.x + 2.f/5.f * dimension_.x,
		position_.y + 3.f/5.f * dimension_.y, "");
}

void HUD::RobotInf::setRobot(Robot* r)
{
	robot_ = r;
	ico_->background_image("ico_tondeuse");
	name_->text(robot_->getName());

	std::stringstream ss ;
	Stats stats = robot_->getFullStats();

	ss << stats.hp.getCurrent();
	speed_->text(ss.str());
	ss.clear();

	ss << robot_->getOrientation().valueDegrees() << "'";
	orientation_->text(ss.str());
	ss.clear();
}

HUD::RobotInf::~RobotInf(void)
{
}