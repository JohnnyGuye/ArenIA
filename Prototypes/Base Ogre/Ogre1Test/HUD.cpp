#include "HUD.h"

using namespace Gorilla;
using namespace Ogre;

//--------------------------------------Buttons clicks
void HUD::ButtonQuit::onClick()
{
	fs_->stop(Scene::EXIT);
}

void HUD::ButtonBackToMain::onClick()
{
	fs_->stop(Scene::LAUNCHER);
}

void HUD::ButtonResume::onClick()
{
	fs_->togglePause();
}
//-------------------------------------- HUD
HUD::HUD(Viewport* vp, FightScene* fs)
	: GUIContext(vp, "HUD"),
	fightScene_(fs),
	fightManager_(fs->getFightManager()),
	hudScale(0.070f)
{
	//this->mouseVisibility(false);
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
		addElement(ri->init(layerHUD_));
		ri->setRobot(*it);

		i++;

	}

	//---Menus

	GUI::Pane* menuPane_ = new GUI::Pane(Vector2(floor(width_ * 0.2f), floor(height_ * 0.1f)), Vector2(floor(width_ * 0.6f), floor(height_ * 0.8f)));
	menuPane_->init(layerMenus_);

	GUI::List* list = new GUI::List(Vector2(width_ * 3 / 8, height_ * 1 / 8), Vector2(width_/4, height_ * 6 / 8));
	list->init(layerMenus_);
	int nbElm = 3;
	auto h = height_/8;
	list->setSpacing((height_ - (nbElm * h)) / (nbElm +1));
	
	auto leave = (new ButtonQuit(Vector2(1), Vector2(h), this->fightScene_))->init(layerMenus_);
	auto back = (new ButtonBackToMain(Vector2(1), Vector2(h), this->fightScene_))->init(layerMenus_);
	auto resume = (new ButtonResume(Vector2(1), Vector2(h), this->fightScene_))->init(layerMenus_);
	//GUI::Button* changeIa = (new GUI::Button(Vector2(1), Vector2(h)))->init(layerMenus_);	
	//changeIa->setText("Changer l'IA d'un robot");

	list->addElement(resume);
	//list->addElement(changeIa);
	list->addElement(back);
	list->addElement(leave);

	menuPane_->addChild(list);

	addElement(menuPane_);

	showMenu(false);
	//---Events
	
	
}

bool HUD::frameRenderingQueued(FrameEvent const& evt)
{
	GUIContext::frameRenderingQueued(evt);
	return true;
}

void HUD::showMenu(bool show)
{
	if (show)
	{
		layerMenus_->show();
		mouseVisibility(true);
	}
	else
	{
		layerMenus_->hide();
		mouseVisibility(false);
	}
}

//-----------------------------------------------------------------------
HUD::RobotInf::RobotInf(Ogre::Vector2 position, Ogre::Vector2 dimension)
	: Pane(position, dimension)
{
}

HUD::RobotInf* HUD::RobotInf::init(Gorilla::Layer* layer)
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

	return this;
}

void HUD::RobotInf::setRobot(Robot* r)
{
	robot_ = r;
	ico_->background_image("ico_tondeuse");
	name_->text(robot_->getName());

	std::stringstream ss ;
	std::stringstream so;
	Stats stats = robot_->getFullStats();

	if(!robot_->isDead())
	{
		ss << stats.hp.getCurrent();
		speed_->text(ss.str());

		so << robot_->getOrientation().valueDegrees() << "'";
		orientation_->text(ss.str());
	}
	else
	{
		speed_->text("The life is not worth");
		orientation_->text("I'll stay proud in death");
	}

	
}

bool HUD::RobotInf::update(const Ogre::FrameEvent& evt)
{
	std::stringstream ss ;
	std::stringstream so;
	Stats stats = robot_->getFullStats();

	if(!robot_->isDead())
	{
		ss << stats.hp.getCurrent();
		speed_->text(ss.str());

		so << robot_->getOrientation().valueDegrees() << "'";
		orientation_->text(ss.str());
	}
	else
	{
		speed_->text("The life is not worth");
		orientation_->text("I'll stay proud in death");
	}

	return true;
}

HUD::RobotInf::~RobotInf(void)
{
}