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
	
	mapList_ = new GUI::List(Vector2(pos.x + 50.f, pos.y + 100.f), dim*0.8f);
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

	//Init layers
	layerBackground_ = screen_->createLayer(0);
	layerBase_ = screen_->createLayer(8);
	layerListArea_ = screen_->createLayer(10);

	//Init selection area
	listArea_ = new GUI::ListArea(Ogre::Vector2(width_ * 0.7f, height_ * 0.0f), 
		Ogre::Vector2(width_ * 0.3f, height_ * 1.f));
	loadAllElements();
	listArea_->init(layerListArea_);
	
	addElement(listArea_);

	loadAllElements();

}

GUILauncher::~GUILauncher(void)
{
	delete listArea_;
}

void GUILauncher::loadAllElements()
{
	// /!\ We use the boost library to go through folders



	//TODO : add robots to myRobots manuallly

	boost::filesystem::path myPath;

	//We repeat the same process for the AIs and the maps.

	myPath = "../IAs";
	boost::filesystem::recursive_directory_iterator iterAI(myPath), eodAI;

	BOOST_FOREACH(boost::filesystem::path const& i, make_pair(iterAI, eodAI)){

		if (is_regular_file(i)){
			std::string fileName = i.string();
			if ( stringEndsWith ( fileName, "lua") )
			{
				myAIs_.push_back( fileName );
			}
		}
	}

	myPath = "../Media/maps";
	boost::filesystem::recursive_directory_iterator iterMaps(myPath), eodMaps;

	BOOST_FOREACH(boost::filesystem::path const& i, make_pair(iterMaps, eodMaps)){

		if (is_regular_file(i)){
			std::string fileName = i.string();
			if ( stringEndsWith ( fileName, "tmx") )
			{
				Terrain mTerrain( fileName );
				myTerrains_.push_back(mTerrain);
			}
		}
	}
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