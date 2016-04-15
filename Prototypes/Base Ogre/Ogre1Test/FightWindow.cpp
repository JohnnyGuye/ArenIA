#include "FightWindow.h"


#include <cstdlib>

using namespace Ogre;
using namespace std;

// ----------------------------------------------
// ---------------- THE SUN ---------------------
// ----------------------------------------------

FightWindow::Sun::Sun(FightWindow* fw = nullptr)
	: fw_(fw), sceneMgr_(fw->sceneMgr_),
	offset_(fw_->fightManager_->getTerrain()->getDimension())
{
	//Entity and position
	Vector3 initPos = Vector3(ORBIT, 0, 500);
	node_ = sceneMgr_->getRootSceneNode()->createChildSceneNode(initPos);

	//Ambient light
	sceneMgr_->setAmbientLight(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
	sceneMgr_->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	
	//SpotLight
	light_ = sceneMgr_->createLight("SunLight");
	light_->setDiffuseColour(0.95f, 0.85f, 0.95f);
	light_->setSpecularColour(0.7f, 0.65f, 0.7f);

	light_->setType(Light::LT_POINT);
	light_->setDirection(Vector3::ZERO);
	light_->setPosition(initPos);
}

FightWindow::Sun::~Sun()
{
}

void FightWindow::Sun::update()
{
	double dayRatio = fw_->fightManager_->getDayRatio();
	Real cos = Math::Cos(dayRatio * Math::PI);
	Real sin = Math::Sin(dayRatio * Math::PI);
	node_->setPosition( cos * ORBIT + offset_.y, sin* ORBIT, offset_.x); 
	light_->setPosition(node_->getPosition());
	Real r(abs(dayRatio * 2 - 1) * 0.4 + 0.6);
	Real v(0.6f);
	Real b(abs(dayRatio * 2 - 1) * (-0.5) + 1.5);
	Real s(abs(dayRatio * 2 - 1) * (-.3) + 1.3);
	light_->setDiffuseColour(r * s, v * s, b * s);
}

// ----------------------------------------------
// --------------- GAME ENTITY ------------------
// ----------------------------------------------

FightWindow::GameEntity::GameEntity(Ogre::SceneManager* sceneMgr, const string& mesh,
	const Ogre::Vector3& position, const int& scale, GameObject* object)
	:	sceneMgr_(sceneMgr),
	object_(object),
	orientation_(0)
{
	entity_ = sceneMgr_->createEntity(mesh); 

	node_ = sceneMgr_->getRootSceneNode()->createChildSceneNode();
	node_->setPosition(position);
	node_->setScale(scale, scale, scale);
	node_->attachObject(entity_);
	node_->pitch(Degree(-90));

	animState_ = entity_->getAnimationState("IDLE");
	animState_->setLoop(true);
	animState_->setEnabled(true);
}

FightWindow::GameEntity::~GameEntity()
{
}

void FightWindow::GameEntity::update(const FrameEvent& evt)
{
	node_->setPosition(object_->getPosition());

	if(object_->getOrientation() != orientation_)
	{
		node_->roll(object_->getOrientation() - orientation_);
		orientation_ = object_->getOrientation();
	}

	animState_->addTime(evt.timeSinceLastFrame);
}

// ----------------------------------------------
// --------------- ROBOT ENTITY -----------------
// ----------------------------------------------

FightWindow::RobotEntity::RobotEntity(Ogre::SceneManager* sceneMgr, const string& mesh,
	const Ogre::Vector3& position, const int& scale, Robot* robot)
	:	GameEntity(sceneMgr, mesh, position, scale, robot)
{
	robot->setOrientation(Degree(0));
	node_->roll(Degree(robot->getOrientation()));
}

FightWindow::RobotEntity::~RobotEntity()
{
}

void FightWindow::RobotEntity::update(const FrameEvent& evt)
{
	Robot* robot = (Robot*)object_;
	animState_ = entity_->getAnimationState(stateToString(robot->getState()));
	GameEntity::update(evt);
}

string FightWindow::RobotEntity::stateToString(const Robot::State& state) const
{
	switch(state){
	case Robot::SHOOTING:
		return "SHOOTING";
	case Robot::IDLE:
	default:
		return "IDLE";
	}
}

// ----------------------------------------------
// ------------ THE FIGHT WINDOW ----------------
// ----------------------------------------------

FightWindow::FightWindow(void)
	: lag_(0),
	fightPanel_(0),
	displaySpeed_(1),
	theSun_(nullptr),
	fightManager_(nullptr),
	state_(GAME)
{
}

FightWindow::~FightWindow(void)
{
	if(theSun_)	delete theSun_;
	if(fightManager_) delete fightManager_;
	if(console_) delete console_;
}


bool FightWindow::setup(void)
{
    root_ = new Ogre::Root(pluginsCfg_);
	fightManager_ = new FightManager("big_map_test.txt");

	//Initialize angles translations
	math_ = new Math(4096);
    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createViews();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    // Create the scene
    createScene();

    createFrameListener();

    return true;
};

void FightWindow::createEntity(const string& mesh, const Vector3& position, const int& scale)
{
	//Add some configuration
	objectEntities_.push_back(GameEntity(sceneMgr_, mesh, position, scale));
}

void FightWindow::createRobot(const std::string& name, const Robot::Type& type, const Robot::Team& team, const Ogre::Vector3& position, const int& scale)
{
	string mesh;
	switch(type){
	case Robot::LAVE_LINGE:
		mesh = "RobotLaveLinge.mesh";
	default:
		mesh = "RobotLaveLinge.mesh";

	}
	Robot* robot = new Robot(position, name, team);
	robotsEntities_.push_back(RobotEntity(sceneMgr_, mesh, position, scale, robot));
	fightManager_->addRobot(robot);
}

void FightWindow::createRobots(void)
{
	std::list<Robot*> robots = fightManager_->getRobots();

	for(std::list<Robot*>::iterator it = robots.begin(); it != robots.end() ; it++ )
	{
		int scale;
		string mesh;
		Robot::Type type = Robot::LAVE_LINGE;
		switch(type)
		{
		case Robot::LAVE_LINGE:
		default:
			scale = 10;
			mesh = "RobotLaveLinge.mesh";
		}
		robotsEntities_.push_back(RobotEntity(sceneMgr_, mesh, (*it)->getPosition(), scale, (*it)));
	}
}

void FightWindow::createViews()
{
	//Cameras
	camera_ = sceneMgr_->createCamera("PlayerCam");
	camera_->setPosition(Ogre::Vector3(0, 300, 500));
	camera_->lookAt(Ogre::Vector3(0, 0, 0));

	camera_->setNearClipDistance(5);
	cameraMan_ = new OgreBites::SdkCameraMan(camera_);

	//Viewportes
	Ogre::Viewport* vp = window_->addViewport(camera_);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	console_ = new GUIConsole(vp);

	camera_->setAspectRatio(
		  Ogre::Real(vp->getActualWidth()) /
		  Ogre::Real(vp->getActualHeight()));
}

void FightWindow::createScene(void)
{
	//======== ABOUT LIGHT =========
	// -- The sun -- //
	theSun_ = new Sun(this);
	sceneMgr_->setSkyBox(true, "ArenIA/SkyBox");

	//======ABOUT THE CAMERA=======
	camera_->setPosition(
		fightManager_->getTerrain()->getWidth() * 50.0, 
		500.0, 
		fightManager_->getTerrain()->getHeight() * 50.0
		);
	//=======ONE ROBOT FOR THE TEST======
	//createRobot("Robot-001", Robot::LAVE_LINGE , Robot::NONE, Vector3(750,10,450), 10);
	createRobots();

	//========THE GROUND=========
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	
	Ogre::MeshManager::getSingleton().createPlane(
	  "ground",
	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  plane, 
	  fightManager_->getTerrain()->getWidth() * Terrain::CELL_SIZE, fightManager_->getTerrain()->getHeight() * Terrain::CELL_SIZE, 10, 10, 
	  true, 
	  1, 5.0f, 5.0f, 
	  Ogre::Vector3::UNIT_X);

	Vector3 offset(fightManager_->getTerrain()->getWidth() * Terrain::CELL_SIZE * 0.5, 
		0, 
		fightManager_->getTerrain()->getHeight() * Terrain::CELL_SIZE * 0.5);

	Ogre::Entity* groundEntity = sceneMgr_->createEntity("ground");
	sceneMgr_->getRootSceneNode()->createChildSceneNode(offset)->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("ArenIA/Ground");

	//========CREATE ENTITIES FROM TERRAIN===========

	unsigned int width = fightManager_->getTerrain()->getWidth();
	unsigned int height = fightManager_->getTerrain()->getHeight();

	for(unsigned int i = 0; i < width; i++)
	{
		for(unsigned int j = 0; j < height; j++)
		{
			GameObject* go = fightManager_->getTerrain()->getObjectInCell(i, j);
			if(go != nullptr)
			{
				SceneryObject* so = (SceneryObject*)go;
				Entity*		decorEntity;
				SceneNode*	node;
				Real		s(50);
				Vector3		offset(Terrain::CELL_SIZE * 0.5, 0, Terrain::CELL_SIZE * 0.5);
				std::string mesh;

				switch(so->getType())
				{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 17:
				case 19:
				case 20:
				case 21:
				case 22:
				case 33:
				case 34:
				case 35:
				case 36:
				case 37:
				case 38:
					mesh = "Wall_basic.mesh";
					break;
				case 18:
					mesh = "Obstacle_basic.mesh";
					break;
				default:
					s = 1;
					mesh = "cube.mesh";
				}
				decorEntity = sceneMgr_->createEntity(mesh);
					
				node = sceneMgr_->getRootSceneNode()->createChildSceneNode(so->getPosition() + offset);
				node->attachObject(decorEntity);
				node->scale(s,s,s);
				node->pitch(Degree(-90));
				DecorEntities_.push_back(decorEntity);
			}
		}
	}
}

void FightWindow::createFrameListener(void)
{
	LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	ostringstream windowHndStr;
	
	window_->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(make_pair("WINDOW", windowHndStr.str()));

	inputManager_ = OIS::InputManager::createInputSystem(pl);

	keyboard_ = static_cast<OIS::Keyboard*>(inputManager_->createInputObject(OIS::OISKeyboard, true));
    mouse_ = static_cast<OIS::Mouse*>(inputManager_->createInputObject(OIS::OISMouse, true));

	mouse_->setEventCallback(this);
	keyboard_->setEventCallback(this);

	 // Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(window_, this);

	inputContext_.mKeyboard = keyboard_;
    inputContext_.mMouse = mouse_;
    trayMgr_ = new OgreBites::SdkTrayManager("InterfaceName", window_, inputContext_, this);
    trayMgr_->showFrameStats(OgreBites::TL_BOTTOMLEFT);

	trayMgr_->hideCursor();

	StringVector items;
	items.push_back("Map");
	items.push_back("Robots");
	items.push_back("Speed");
	items.push_back("");
	items.push_back("Filtering");
	items.push_back("Poly Mode");

	fightPanel_ = trayMgr_->createParamsPanel(OgreBites::TL_TOPLEFT, "Fight !", 400, items);
	fightPanel_->setParamValue(4, "Bilinear");
    fightPanel_->setParamValue(5, "Solid");

	root_->addFrameListener(this);
}

/* GAME LOOP MODAFUCKERS */
bool FightWindow::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	//Not really the game
    if(window_->isClosed())
        return false;

    if(shutDown_)
        return false;

    // Need to capture/update each device
    keyboard_->capture();
    mouse_->capture();

	/* OVERLAY */
    trayMgr_->frameRenderingQueued(evt);

    if (!trayMgr_->isDialogVisible())
    {
        cameraMan_->frameRenderingQueued(evt);   // If dialog isn't up, then update the camera
        if (fightPanel_->isVisible())          // If details panel is visible, then update its contents
        {
			fightPanel_->setParamValue(0, fightManager_->getTerrain()->getName());
			fightPanel_->setParamValue(1, StringConverter::toString(robotsEntities_.size()));
			fightPanel_->setParamValue(2, StringConverter::toString(displaySpeed_));
        }
    }

	/* LOGIC */
	for(lag_ += (evt.timeSinceLastFrame * 1000 * 1000 * displaySpeed_) ; lag_ >= (GameTime::ROUND_IN_MS) ; lag_ -= (GameTime::ROUND_IN_MS))
	{
		fightManager_->update();
	}
	

	/* RENDERING */
	theSun_->update();

	for(std::list<GameEntity>::iterator ge = objectEntities_.begin() ; ge != objectEntities_.end() ; ge++)
	{
		(*ge).update(evt);
	}

	for(std::list<RobotEntity>::iterator re = robotsEntities_.begin() ; re != robotsEntities_.end() ; re++)
	{
		(*re).update(evt);
	}

	console_->frameStarted(evt);

    return true;
}

bool FightWindow::keyPressed( const OIS::KeyEvent& arg)
{
	if (trayMgr_->isDialogVisible()) return true;   // don't process any more keys if dialog is up

	switch(state_)
	{
	case GAME:
		switch(arg.key)
		{
		case OIS::KC_F:
			trayMgr_->toggleAdvancedFrameStats();
			break;
		case OIS::KC_G:
			if (fightPanel_->getTrayLocation() == OgreBites::TL_NONE)
			{
				trayMgr_->moveWidgetToTray(fightPanel_, OgreBites::TL_TOPLEFT, 0);
				fightPanel_->show();
			}
			else
			{
				trayMgr_->removeWidgetFromTray(fightPanel_);
				fightPanel_->hide();
			}
			break;
		case OIS::KC_T:
			{
				Ogre::String newVal;
				Ogre::TextureFilterOptions tfo;
				unsigned int aniso;

				switch (fightPanel_->getParamValue(4).asUTF8()[0])
				{
				case 'B':
					newVal = "Trilinear";
					tfo = Ogre::TFO_TRILINEAR;
					aniso = 1;
					break;
				case 'T':
					newVal = "Anisotropic";
					tfo = Ogre::TFO_ANISOTROPIC;
					aniso = 8;
					break;
				case 'A':
					newVal = "None";
					tfo = Ogre::TFO_NONE;
					aniso = 1;
					break;
				default:
					newVal = "Bilinear";
					tfo = Ogre::TFO_BILINEAR;
					aniso = 1;
				}
				Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
				Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
				fightPanel_->setParamValue(5, newVal);
			}
		case OIS::KC_R:
			{
				Ogre::String newVal;
				Ogre::PolygonMode pm;

				switch (camera_->getPolygonMode())
				{
				case Ogre::PM_SOLID:
					newVal = "Wireframe";
					pm = Ogre::PM_WIREFRAME;
					break;
				case Ogre::PM_WIREFRAME:
				default:
					newVal = "Solid";
					pm = Ogre::PM_SOLID;
				}

				camera_->setPolygonMode(pm);
				fightPanel_->setParamValue(5, newVal);
			}
		case OIS::KC_SUBTRACT:
			if(displaySpeed_ > 0.25) displaySpeed_ *= 0.5;
			break;
		case OIS::KC_ADD:
			if(displaySpeed_ < 16) displaySpeed_ *= 0.5;
			break;
		case OIS::KC_SYSRQ:
			window_->writeContentsToTimestampedFile("screenshot", ".jpg");
			break;
		}
		cameraMan_->injectKeyDown(arg);
	case CONSOLE_ON:
		console_->onKeyPressed(arg);
		break;

	}
    if (arg.key == OIS::KC_ESCAPE)
    {
        shutDown_ = true;
    }
	else if (arg.key == OIS::KC_F1)
	{
		if(console_->isVisible())
		{
			console_->setVisible(false);
			state_ = GAME;
		}
		else
		{
			console_->setVisible(true);
			state_ = CONSOLE_ON;
		}
	}

	
    
    return true;
}