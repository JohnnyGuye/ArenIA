#include "GUILauncher.h"
#include "LauncherScene.h"


#include <OGRE\OgrePrerequisites.h>

using namespace Ogre;
using namespace std;


/*********************************************************
***************** List AREA ******************************
*********************************************************/
GUI::ListArea::ListArea(const Ogre::Vector2& pos,const Ogre::Vector2& dim, LauncherScene* ls)
	: Pane(pos, dim),
	robotList_(nullptr),
	AIList_(nullptr),
	mapList_(nullptr),
	ls_(ls)
{
	Vector2 logoDimensions = Vector2(dim.x*0.25f, dim.y*0.15f);
	areniaLogo_ = new GUI::Button(Vector2(pos.x + (this->getParent()->getDimension().x - logoDimensions.x)/2.f, pos.y), logoDimensions);
	robotList_ = new GUI::List(Vector2(pos.x, pos.y + areniaLogo_->getDimension().y*1.01f), dim*0.3f);
	AIList_ = new GUI::List(Vector2(pos.x + robotList_->getDimension().x + dim.x*0.01f, pos.y + areniaLogo_->getDimension().y*1.01f), dim*0.3f);
	mapList_ = new GUI::List(Vector2(pos.x + ( robotList_->getDimension().x + dim.x*0.01f ) *2, pos.y + areniaLogo_->getDimension().y*1.01f), dim*0.3f);
}

GUI::ListArea* GUI::ListArea::init(Gorilla::Layer* layer)
{
	if(initialized_)	return this;
	initialized_ = true;

	layerBack_ = layer;
	background_ = layerBack_->createRectangle(position_, dimension_);
	background_->background_colour(Gorilla::Colours::DimGray);
	background_->border(5.f, Gorilla::Colours::AliceBlue);

	addChild(areniaLogo_->init(layer));
	areniaLogo_->setBackground("arenia_logo");
	areniaLogo_->setText("");

	//Robot list
	addChild(robotList_->init(layer));
	for (unsigned int i = 0 ; i < myRobots_.size() ; i++ )
	{
		Robot * robot = myRobots_.at(i);
		std::string label = robot->getName();
		auto button = new GUI::RobotButton(position_, Ogre::Vector2(200,100), ls_, robot);
		button->init(layer);
		button->setBackground("button_bg");
		button->setText(label);
		robotList_->addElement(button);
	}

	//IA list
	addChild(AIList_->init(layer));
	std::string extension = ".lua";
	for (unsigned int i = 0 ; i < myAIs_.size() ; i++ )
	{
		std::string label = myAIs_.at(i)->substr(0, myAIs_.at(i)->length() - extension.length());
		auto button = new GUI::AIButton(position_, Ogre::Vector2(200,100), ls_, *myAIs_.at(i));
		button->init(layer);
		button->setBackground("button_bg");
		button->setText(label);
		AIList_->addElement(button);
	}

	//Map list
	addChild(mapList_->init(layer));
	extension = ".txt";
	for (unsigned int i = 0 ; i < myTerrains_.size() ;  i++ )
	{
		Terrain * terrain = myTerrains_.at(i);
		std::string label = terrain->getName();
		
		label = label.substr(0, label.length() - extension.length());

		auto button = new GUI::TerrainButton(position_, Ogre::Vector2(200,100), ls_, terrain);
		button->init(layer);
		button->setBackground("button_bg");
		button->setText(label);
		mapList_->addElement(button);
	}

	return this;
}

GUI::ListArea::~ListArea()
{
	if(initialized_)
	{
		layerBack_->destroyRectangle(background_);
	}
}

void GUI::ListArea::update()
{
	dirty_ = false;
}

void GUI::ListArea::resize(Ogre::Vector2 dimension)
{
	//TODO
}

bool GUI::ListArea::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(dirty_)	update();
	return true;
}

void GUI::ListArea::loadAllElements()
{
	//We first add the robots manually
	myRobots_.push_back(new MowerRobot(Ogre::Vector3::ZERO, "MowerRobot", Robot::NONE));
	myRobots_.push_back(new WasheeRobot(Ogre::Vector3::ZERO, "WasheeRobot", Robot::NONE));


	boost::filesystem::path myPath;

	// /!\ We use the boost library to go through folders
	//We do the same thing for the AIs and the maps : 
	//We go through the files in the corresponding folders,
	//and select the ones with the right extensions

	myPath = "../IAs";
	std:: string pathName = myPath.string();
	boost::filesystem::recursive_directory_iterator iterAI(myPath), eodAI;

	BOOST_FOREACH(boost::filesystem::path const& i, make_pair(iterAI, eodAI)){

		if (is_regular_file(i)){
			std::string fileName = i.string();
			fileName = fileName.substr(pathName.length()+1);
			if ( stringEndsWith ( fileName, "lua") )
			{
				std::string* aiName = new string(fileName);
				myAIs_.push_back( aiName );
			}
		}
	}

	myPath = "../Media/maps";
	pathName = myPath.string();

	boost::filesystem::recursive_directory_iterator iterMaps(myPath), eodMaps;
	
	BOOST_FOREACH(boost::filesystem::path const& i, make_pair(iterMaps, eodMaps)){

		if (is_regular_file(i)){
			std::string fileName = i.string();
			std::string extension = "txt";
			fileName = fileName.substr(pathName.length()+1);
			
			if ( stringEndsWith ( fileName , extension) )
			{				
				Terrain * mTerrain = new Terrain( fileName );
				myTerrains_.push_back(mTerrain);
			}
		}
	}
	
}


FightInformations * GUI::ListArea::getFightInformations()
{
	return ls_->getFightInformations();
}

void GUI::ListArea::setFightInformationsRobot( Robot * mRobot)
{
	delete ls_->getFightInformations()->robot;
	ls_->getFightInformations()->robot = mRobot;
}

void GUI::ListArea::setFightInformationsAI(const std::string& mAI)
{
	ls_->getFightInformations()->ai = mAI;
}

void GUI::ListArea::setFightInformationsTerrain( Terrain * mTerrain)
{
	delete ls_->getFightInformations()->terrain;
	ls_->getFightInformations()->terrain = mTerrain;
}

/*********************************************************
*********************** PlayButton ***********************
*********************************************************/
GUI::PlayButton::PlayButton(Ogre::Vector2 position, Ogre::Vector2 dimension, ::LauncherScene* ls)
	: Button(position, dimension),
	ls_(ls)
{
}

GUI::PlayButton::~PlayButton()
{
}

void GUI::PlayButton::onClick()
{
	ls_->stop(Scene::FIGHT);
}

/*********************************************************
*********************** ListButton **********************
*********************************************************/
GUI::ListButton::ListButton(Ogre::Vector2 position, Ogre::Vector2 dimension, LauncherScene* ls)
	: Button(position, dimension),
	ls_(ls)
{
}

GUI::ListButton::~ListButton()
{
}

/*********************************************************
*********************** RobotButton **********************
*********************************************************/
GUI::RobotButton::RobotButton(Ogre::Vector2 position, Ogre::Vector2 dimension, LauncherScene* ls,  Robot * robot)
	: ListButton(position, dimension, ls),
	robot_(robot)
{
}

GUI::RobotButton::~RobotButton()
{
}

void GUI::RobotButton::onClick()
{
	ls_->getFightInformations()->robot = robot_;
}

/*********************************************************
*********************** AIButton *************************
*********************************************************/
GUI::AIButton::AIButton(Ogre::Vector2 position, Ogre::Vector2 dimension, LauncherScene* ls, const std::string& ai)
	: ListButton(position, dimension, ls),
	ai_(ai)
{
}

GUI::AIButton::~AIButton()
{
}

void GUI::AIButton::onClick()
{
	ls_->getFightInformations()->ai = ai_;
}
		

/*********************************************************
*********************** TerrainButton ********************
*********************************************************/
GUI::TerrainButton::TerrainButton(Ogre::Vector2 position, Ogre::Vector2 dimension, LauncherScene* ls,  Terrain * terrain)
	: ListButton(position, dimension, ls),
	terrain_(terrain)
{
}

GUI::TerrainButton::~TerrainButton()
{
}

void GUI::TerrainButton::onClick()
{
	
	ls_->getFightInformations()->terrain = terrain_;
}

/*********************************************************
*********************** GUILauncher **********************
*********************************************************/
GUILauncher::GUILauncher(Ogre::Viewport* vp, LauncherScene* ls)
	: GUIContext(vp, "HUDFlowChart"),
	listArea_(nullptr),
	mouse_(nullptr),
	ls_(ls)
{
	width_ = screen_->getWidth();
	height_ = screen_->getHeight();

	//Init layers
	layerBackground_ = screen_->createLayer(0);
	layerBase_ = screen_->createLayer(8);
	layerListArea_ = screen_->createLayer(10);

	//Init selection area
	listArea_ = new GUI::ListArea(Ogre::Vector2(width_ * 0.0f, height_ * 0.0f), 
		Ogre::Vector2(width_ * 1.0f, height_ * 1.0f)
		, ls);
	listArea_->loadAllElements();
	listArea_->init(layerListArea_);

	Vector2 playDimension = Ogre::Vector2(width_/16 , height_ /16);
	auto playButton = new GUI::PlayButton(
		Vector2(width_ - playDimension.x*2 , height_ - playDimension.y*2),
		playDimension, 
		ls);
	addElement(playButton->init(layerListArea_));
	playButton->setBackground("button_bg");
	playButton->setText("PLAY");
	
	this->addElement(listArea_);
}

GUILauncher::~GUILauncher(void)
{
	delete listArea_;
}



bool GUILauncher::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	GUIContext::frameRenderingQueued(evt);
	return true;
}

//==== Util ==== 
bool stringStartsWith(std::string myString, std::string myStringFragment)
{
	if (myString.length() >= myStringFragment.length()) {
        return (0 == myString.compare (0, myStringFragment.length(), myStringFragment));
    } else {
        return false;
    }
}

bool stringEndsWith(std::string myString, std::string myStringFragment)
{
	if (myString.length() >= myStringFragment.length()) {
        return (0 == myString.compare (myString.length() - myStringFragment.length(), myStringFragment.length(), myStringFragment));
    } else {
        return false;
    }
}