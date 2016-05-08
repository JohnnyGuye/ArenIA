#include "GUILauncher.h"


#include <OGRE\OgrePrerequisites.h>


/*********************************************************
***************** List AREA ************************
*********************************************************/
GUI::ListArea::ListArea(const Ogre::Vector2& pos,const Ogre::Vector2& dim)
	: dirty_(true),
	initialised_(false),
	pos_(pos),
	dim_(dim)

{
}

void GUI::ListArea::init(Gorilla::Layer* layer)
{
	initialised_ = true;
	layerBack_ = layer;
	background_ = layerBack_->createRectangle(pos_, dim_);
	background_->background_image("rect_violet");

	/*
	Blocks_.push_back(new Start(layer, Ogre::Vector2(600, 200)));
	Blocks_.push_back(new End(layer, Ogre::Vector2(600, 400)));
	*/
	//We load the lists of robos/AIs/maps

}

GUI::ListArea::~ListArea()
{
	if(!initialised_)
		return;
}

void GUI::ListArea::update()
{
	dirty_ = false;
}

bool GUI::ListArea::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(dirty_)
		update();
	return true;
}

bool GUI::ListArea::mouseMoved(const OIS::MouseEvent &arg)
{

}

bool GUI::ListArea::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{

	return true;
}

bool GUI::ListArea::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{

}

/*********************************************************
**********************Blocks******************************
*********************************************************/

/** Basic Block **/
GUI::ListArea::Block::Block(Gorilla::Layer* layer, Ogre::Vector2 pos, Ogre::Vector2 dim, const Ogre::String& sprite, blockTypes blockType)
	: layer_(layer),
	onHold_(false),
	rect_(nullptr),
	hitBox_(nullptr),
	blockType_(blockType)
{
	rect_ = layer_->createRectangle(pos, dim);
	rect_->background_image(sprite);
	
}

GUI::ListArea::Block::~Block()
{
	layer_->destroyRectangle(rect_);
}

bool GUI::ListArea::Block::mouseMoved(const OIS::MouseEvent &arg)
{
	Ogre::Vector2 mp((float)arg.state.X.abs, (float)arg.state.Y.abs);

	Ogre::Real nX = mp.x + topLeftDist_.x,
		nY = mp.y + topLeftDist_.y;

	bool intersect = false;
	if(onHold_)
	{
		rect_->left(nX);
		rect_->top(nY);
		hitBox_->left(nX);
		hitBox_->top(nY);
	}
	else
	{
		if(hitBox_->intersects(mp))
		{
			hitBox_->border(5, Gorilla::Colours::White);
			intersect = true;
		}
		else
		{
			hitBox_->border(2, Gorilla::Colours::Black);
			intersect = false;
		}
		
		
	}
	return intersect;
}

bool GUI::ListArea::Block::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	Ogre::Vector2 mousePosition(Ogre::Real(arg.state.X.abs),Ogre::Real(arg.state.Y.abs));
	if(hitBox_->intersects(mousePosition))
	{
		onHold_ = true;
		topLeftDist_ = Ogre::Vector2(hitBox_->left(), hitBox_->top()) - mousePosition;
		return true;
	}
	return false;
}

bool GUI::ListArea::Block::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if(onHold_) onHold_ = false;
	return true;
}

/** Robot Block **/
GUI::ListArea::RobotBlock::RobotBlock( Gorilla::Layer* layer, Ogre::Vector2 pos, Robot* robot)
	: Block(layer, pos, Ogre::Vector2(60,60), "hexa_orange", ROBOT)
{
	hitBox_ = layer_->createPolygon(pos.x, pos.y, 30, 6);
	hitBox_->angle(Ogre::Degree(90.f));
	hitBox_->no_background();
	robot_ = robot;
}


/*********************************************************
**********************BlockList***************************
*********************************************************/
GUI::ListArea::BlockList::BlockList(Gorilla::Layer* layer, Ogre::Vector2 pos, Ogre::Vector2 dim, const Ogre::String& sprite, blockTypes blockType)
	: layer_(layer),
	rect_(nullptr),
	hitBox_(nullptr),
	blockType_(blockType)
{
	rect_ = layer_->createRectangle(pos, dim);
	rect_->background_image(sprite);

	switch(blockType)
	{
	case ROBOT:
		
		for (std::list<Robot>::iterator iterator = GUILauncher::robots_.begin(), end = GUILauncher::robots_.end(); iterator != end; ++iterator)
		{
			blocks_.push_back( new RobotBlock( layer, Ogre::Vector2(600, 200), &(*iterator) ) );
		}
		
		break;
	case AI:

		break;

	case MAP:

		break;

	default:
		break;
	}
		
}

GUI::ListArea::BlockList::BlockList()
{
}

GUI::ListArea::BlockList::~BlockList()
{
}

std::list<GUI::ListArea::Block*> GUI::ListArea::BlockList::getBlocks()
{
	return blocks_;
}

bool GUI::ListArea::BlockList::mouseMoved(const OIS::MouseEvent &arg)
{
}
bool GUI::ListArea::BlockList::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
}
bool GUI::ListArea::BlockList::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
}

/*********************************************************
*********************** GUILauncher **************************
*********************************************************/
GUILauncher::GUILauncher(Ogre::Viewport* vp)
	: GUIElement(vp, "HUDFlowChart"),
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

	mouse_ = layerTop_->createRectangle(width_ / 2, height_ / 2, 20, 20);
	mouse_->background_image("mousepointer");

	loadAllElements();
	listArea_ = new GUI::ListArea(Ogre::Vector2(width_ * 0.1f, height_ * 0.01f), 
		Ogre::Vector2(width_ * 0.8f, height_ * 0.98f));

	listArea_->init(layerListArea_);

	std::list<Robot> robots_;
	std::list<std::string> ais_;
	std::list<Terrain> maps_;
}

GUILauncher::~GUILauncher(void)
{
	delete listArea_;
}

bool GUILauncher::loadFile(const Ogre::String& fileName)
{
	std::stringstream ss;
	ss << "../IAs/" << fileName;

	std::stringstream file;

	std::ifstream code(ss.str().c_str());

	if(!code)	return false;

	std::string read;
	while(std::getline(code, read))
	{
		
	}

	code.close();
	return true;
}

bool GUILauncher::stringHasEnding(std::string &myString, std::string const &ending)
{
	if (myString.length() >= ending.length())
	{
        return ( 0 == myString.compare ( myString.length() - ending.length(), ending.length(), ending ) );
    }
	else
	{
       return false;
    }

}

bool GUILauncher::stringHasBeginning(std::string &myString, std::string const &beginning)
{
	if (myString.length() >= beginning.length())
	{
        return ( 0 == myString.compare ( 0, beginning.length(), beginning ) );
    }
	else
	{
       return false;
    }

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

mapObjects * GUILauncher::getmapObjects()
{
	return mapObjects_;
}

bool GUILauncher::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	//textArea_->frameRenderingQueued(evt);
	listArea_->frameRenderingQueued(evt);
	return true;
}

bool GUILauncher::mouseMoved(const OIS::MouseEvent &arg)
{
	Ogre::Real x((float)arg.state.X.abs), 
		y((float)arg.state.Y.abs);
	mouse_->left(x);
	mouse_->top(y);
	listArea_->mouseMoved(arg);
	return true;
}

bool GUILauncher::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	listArea_->mousePressed(arg, id);
	return true;
}

bool GUILauncher::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	listArea_->mouseReleased(arg, id);
	return true;
}