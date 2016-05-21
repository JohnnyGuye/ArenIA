#include "GUILauncher.h"


#include <OGRE\OgrePrerequisites.h>

using namespace Ogre;
using namespace std;


/*********************************************************
***************** List AREA ******************************
*********************************************************/
GUI::ListArea::ListArea(const Ogre::Vector2& pos,const Ogre::Vector2& dim)
	: Pane(pos, dim),
	robotList_(nullptr),
	AIList_(nullptr),
	mapList_(nullptr)
{
	robotList_ = new GUI::List(Vector2(pos.x, pos.y), dim*0.3f);
	AIList_ = new GUI::List(Vector2(pos.x + robotList_->getDimension().x + dim.x*0.01f, pos.y), dim*0.3f);
	mapList_ = new GUI::List(Vector2(pos.x + ( robotList_->getDimension().x + dim.x*0.01f ) *2, pos.y), dim*0.3f);
}

GUI::ListArea* GUI::ListArea::init(Gorilla::Layer* layer)
{
	if(initialized_)	return this;
	initialized_ = true;

	layerBack_ = layer;

	background_ = layerBack_->createRectangle(position_, dimension_);
	background_->background_colour(Gorilla::Colours::Gray);
	background_->border(5.f, Gorilla::Colours::AliceBlue);

	/* Example
	addChild(mapList_->init(layer));
	auto firstButton = new GUI::Button(position_, Ogre::Vector2(200,100));
	firstButton->init(layer);
	firstButton->setBackground("button_bg");
	mapList_->addElement(firstButton);

	auto secondButton = new GUI::Button(Ogre::Vector2(100,100), Ogre::Vector2(200,300));
	secondButton->init(layer);
	secondButton->setBackground("button_bg");
	mapList_->addElement(secondButton);
	*/
	
	
	addChild(robotList_->init(layer));
	for ( int i = 0 ; i < myRobots_.size() ; i++ )
	{
		Robot * robot = myRobots_.at(i);
		std::string label = robot->getName();
		auto button = new GUI::Button(position_, Ogre::Vector2(200,100));
		button->init(layer);
		button->setBackground("button_bg");
		button->setText(label);
		robotList_->addElement(button);
	}


	addChild(AIList_->init(layer));

	std::string extension = ".lua";
	for ( int i = 0 ; i < myAIs_.size() ; i++ )
	{
		std::string label = myAIs_.at(i)->substr(0, myAIs_.at(i)->length() - extension.length());
		auto button = new GUI::Button(position_, Ogre::Vector2(200,100));
		button->init(layer);
		button->setBackground("button_bg");
		button->setText(label);
		AIList_->addElement(button);
	}

	
	addChild(mapList_->init(layer));

	extension = ".txt";
	for ( int i = 0 ; i < myTerrains_.size() ;  i++ )
	{
		Terrain * terrain = myTerrains_.at(i);
		std::string label = terrain->getName();
		
		label = label.substr(0, label.length() - extension.length());

		auto button = new GUI::Button(position_, Ogre::Vector2(200,100));
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
				//std::cout << mapName << std::endl;
				Terrain * mTerrain = new Terrain( fileName );
				myTerrains_.push_back(mTerrain);
			}
		}
	}
	
}




/*********************************************************
*********************** GUILauncher **************************
*********************************************************/
GUILauncher::GUILauncher(Ogre::Viewport* vp)
	: GUIContext(vp, "HUDFlowChart"),
	listArea_(nullptr),
	mouse_(nullptr),
	mapObjects_(nullptr)
{
	width_ = screen_->getWidth();
	height_ = screen_->getHeight();

	//Init layers
	layerBackground_ = screen_->createLayer(0);
	layerBase_ = screen_->createLayer(8);
	layerListArea_ = screen_->createLayer(10);

	//Init selection area
	listArea_ = new GUI::ListArea(Ogre::Vector2(width_ * 0.0f, height_ * 0.0f), 
		Ogre::Vector2(width_ * 1.f, height_ * 1.f));
	listArea_->loadAllElements();
	listArea_->init(layerListArea_);
	
}

GUILauncher::~GUILauncher(void)
{
	delete listArea_;
}


MapObjects * GUILauncher::getmapObjects()
{
	return mapObjects_;
}

void GUILauncher::setMapObjectsRobot( Robot * mRobot)
{
	mapObjects_->robot = mRobot;
}
void GUILauncher::setMapObjectsAI( std::string * mAI)
{
	mapObjects_->ai = mAI;
}
void GUILauncher::setMapObjectsTerrain( Terrain * mTerrain)
{
	mapObjects_->terrain = mTerrain;
}

bool GUILauncher::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	listArea_->frameRenderingQueued(evt);
	return true;
}

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