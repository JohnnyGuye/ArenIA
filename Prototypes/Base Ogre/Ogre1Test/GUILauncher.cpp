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
	IAList_(nullptr),
	mapList_(nullptr)
{
	
	mapList_ = new GUI::List(Vector2(pos.x + 50, pos.y + 100), dim*0.8);
}

GUI::ListArea* GUI::ListArea::init(Gorilla::Layer* layer)
{
	if(initialized_)	return this;
	initialized_ = true;

	layerBack_ = layer;

	background_ = layerBack_->createRectangle(position_, dimension_);
	background_->background_colour(Gorilla::Colours::Bisque);
	background_->border(5.f, Gorilla::Colours::Orange);

	addChild(mapList_->init(layer));
	auto firstButton = new GUI::Button(position_, Ogre::Vector2(200,100));
	firstButton->init(layer);
	firstButton->setBackground("rect_violet");
	mapList_->addElement(firstButton);

	auto secondButton = new GUI::Button(Ogre::Vector2(100,100), Ogre::Vector2(200,300));
	secondButton->init(layer);
	secondButton->setBackground("rect_violet");
	mapList_->addElement(secondButton);

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

	layerBackground_ = screen_->createLayer(0);
	layerBase_ = screen_->createLayer(8);
	layerListArea_ = screen_->createLayer(10);
	layerTop_ = screen_->createLayer(15);

	mouse_ = layerTop_->createRectangle(0, 0, 20, 20);
	mouse_->background_image("mousepointer");

	loadAllElements();
	listArea_ = new GUI::ListArea(Ogre::Vector2(width_ * 0.7f, height_ * 0.0f), 
		Ogre::Vector2(width_ * 0.3f, height_ * 1.f));

	listArea_->init(layerListArea_);
	
	addElement(listArea_);
}

GUILauncher::~GUILauncher(void)
{
	delete listArea_;
}

void GUILauncher::loadAllElements()
{
	// /!\ We use the boost library to go through folders

	//We first load all robots. We go through the ../Media/models directory, 
	//we find the robots models and instanciate them to get their stats.
	/*
	std::string myPath = "../Media/models";
	boost::filfilesystem::recursive_directory_iterator iterRobots(myPath), eodRobots;
	Ogre::fil
	BOOST_FOREACH(boost::filesystem::path const& i, make_pair(iterRobots, eodRobots)){

		if (is_regular_file(i)){
			std::string fileName = i.string();
			if ( stringHasBeginning( fileName, "Robot" ) && stringHasEnding ( fileName, "mesh") )
			{
				Robot mRobot(Ogre::Vector3::ZERO, fileName, NONE);
				robots_.push_back(mRobot);
			}
		}
	}

	//We repeat the same process for the AIs and the maps.

	myPath = "../IAs";
	boost::filesystem::recursive_directory_iterator iterAI(myPath), eodAI;

	BOOST_FOREACH(boost::filesystem::path const& i, make_pair(iterAI, eodAI)){

		if (is_regular_file(i)){
			std::string fileName = i.string();
			if ( stringHasEnding ( fileName, "lua") )
			{
				ais_.push_back( fileName.resize( 4 ) );
			}
		}
	}

	myPath = "../Media/maps";
	boost::filesystem::recursive_directory_iterator iterMaps(myPath), eodMaps;

	BOOST_FOREACH(boost::filesystem::path const& i, make_pair(iterMaps, eodMaps)){

		if (is_regular_file(i)){
			std::string fileName = i.string();
			if ( stringHasEnding ( fileName, "tmx") )
			{
				Terrain mTerrain( fileName );
				mas_.push_back(mTerrain);
			}
		}
	}*/
}

MapObjects * GUILauncher::getmapObjects()
{
	return mapObjects_;
}

bool GUILauncher::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	listArea_->frameRenderingQueued(evt);
	return true;
}

bool GUILauncher::mouseMoved(const OIS::MouseEvent &arg)
{
	GUIContext::mouseMoved(arg);
	Ogre::Real x((float)arg.state.X.abs), 
		y((float)arg.state.Y.abs);
	mouse_->left(x);
	mouse_->top(y);
	return true;
}