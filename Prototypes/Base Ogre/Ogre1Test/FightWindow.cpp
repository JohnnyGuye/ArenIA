#include "FightWindow.h"

using namespace Ogre;
using namespace std;

// ----------------------------------------------
// ---------------- THE SUN ---------------------
// ----------------------------------------------

FightWindow::Sun::Sun(FightWindow* fw = nullptr)
	: fw_(fw), sceneMgr_(fw->sceneMgr_)
{
	//Entity and position
	double initX = -fw_->fightManager_->getRemainingTime() / 2;
	Vector3 initPos = Vector3(initX, 1000, 500);
	sun_ = sceneMgr_->createEntity("sphere.mesh");
	sceneMgr_->getRootSceneNode()->createChildSceneNode(initPos)->attachObject(sun_);

	//Ambient light
	sceneMgr_->setAmbientLight(Ogre::ColourValue(0.9f, 0.85f, 0.85f));
	sceneMgr_->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

	//SpotLight
	light_ = sceneMgr_->createLight("SunLight");
	light_->setDiffuseColour(1.0, 1.0, 0.8f);
	light_->setSpecularColour(1.0, 1.0, 0.8f);

	light_->setType(Light::LT_SPOTLIGHT);
	light_->setDirection(Vector3::ZERO);
	light_->setPosition(initPos);
	light_->setSpotlightRange(Degree(45), Degree(50));	
}

FightWindow::Sun::~Sun()
{
}

void FightWindow::Sun::update()
{
	Ogre::Node*node = sun_->getParentNode();
	if(fw_->fightManager_->getActualTime() < fw_->fightManager_->getRemainingTime())
	{
		node->translate(1,1,0);
	}
	else
	{
		node->translate(1,-1,0);
	}
	light_->setPosition(node->getPosition());
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

	animState_ = entity_->getAnimationState("Forward");
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
	robot->setOrientation(Degree(75));
	node_->roll(Degree(robot->getOrientation()));
}

FightWindow::RobotEntity::~RobotEntity()
{
}

void FightWindow::RobotEntity::update(const FrameEvent& evt)
{
	GameEntity::update(evt);
}

// ----------------------------------------------
// ------------ THE FIGHT WINDOW ----------------
// ----------------------------------------------

FightWindow::FightWindow(void)
{
	fightManager_ = new FightManager("essai2.txt");
}

FightWindow::~FightWindow(void)
{
	if(theSun_)	delete theSun_;
}

void FightWindow::setupResources(void)
{
	BaseFightWindow::setupResources();
}

void FightWindow::loadResources(void)
{
	
	BaseFightWindow::loadResources();

	//CEGUI
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing CEGUI ***");
	renderer_ = &CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
}

void FightWindow::createEntity(const string& mesh, const Vector3& position, const int& scale)
{
	//Add some configuration
	objectEntities_.push_back(GameEntity(sceneMgr_, mesh, position, scale));
}

void FightWindow::createRobot(const string& mesh, const Vector3& position, const int& scale, Robot* robot)
{
	//Add some configuration
	robot->setPosition(position);
	robotsEntities_.push_back(RobotEntity(sceneMgr_, mesh, position, scale, robot));
}

void FightWindow::createScene(void)
{

	//======== ABOUT LIGHT =========
	// -- The sun -- //
	theSun_ = new Sun(this);
	sceneMgr_->setSkyBox(true, "Examples/SpaceSkyBox");

	//======ABOUT THE CAMERA=======
	camera_->setPosition(
		fightManager_->getTerrain()->getWidth() * 50.0, 
		300.0, 
		fightManager_->getTerrain()->getWidth() * 50.0
		);
	//=======ONE ROBOT FOR THE TEST======
	//createEntity("RobotLaveLinge.mesh", Vector3(550,0,250), 40);
	createRobot("RobotLaveLinge.mesh", Vector3(650,0,350), 50, new Robot());

	//========THE GROUND=========
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	
	Ogre::MeshManager::getSingleton().createPlane(
	  "ground",
	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  plane, 
	  4000, 4000, 40, 40, 
	  true, 
	  1, 5, 5, 
	  Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = sceneMgr_->createEntity("ground");
	sceneMgr_->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Rockwall");

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
				Ogre::Entity* decorEntity;
				Ogre::SceneNode* node;
				decorEntity = sceneMgr_->createEntity("cube.mesh");
				node = sceneMgr_->getRootSceneNode()->createChildSceneNode(go->getPosition() + Ogre::Vector3(50,50,50));
				node->attachObject(decorEntity);
				DecorEntities_.push_back(decorEntity);
			}
		}
	}
}

void FightWindow::createCamera()
{
	camera_ = sceneMgr_->createCamera("PlayerCam");
	camera_->setPosition(Ogre::Vector3(0, 300, 500));
	camera_->lookAt(Ogre::Vector3(0, 0, 0));

	camera_->setNearClipDistance(5);
	cameraMan_ = new OgreBites::SdkCameraMan(camera_);

}

void FightWindow::createViewports(void)
{
	Ogre::Viewport* vp = window_->addViewport(camera_);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	camera_->setAspectRatio(
		  Ogre::Real(vp->getActualWidth()) /
		  Ogre::Real(vp->getActualHeight()));
}

void FightWindow::createFrameListener(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
 
    window_->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
 
    inputManager_ = OIS::InputManager::createInputSystem( pl );
 
    keyboard_ = static_cast<OIS::Keyboard*>(inputManager_->createInputObject( OIS::OISKeyboard, true ));
    mouse_ = static_cast<OIS::Mouse*>(inputManager_->createInputObject( OIS::OISMouse, true ));
 
    mouse_->setEventCallback(this);
    keyboard_->setEventCallback(this);
 
    //Set initial mouse clipping size
    windowResized(window_);
 
    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(window_, this);

    root_->addFrameListener(this);
}

/* Render loop */
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

	//Need to inject timestamps to CEGUI System.
	try{
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
	}catch(CEGUI::Exception e){
		MessageBox(NULL, e.getMessage().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		 exit(1);

	}
	
	/*
    trayMgr_->frameRenderingQueued(evt);

    if (!trayMgr_->isDialogVisible())
    {
        cameraMan_->frameRenderingQueued(evt);   // If dialog isn't up, then update the camera
        if (detailsPanel_->isVisible())          // If details panel is visible, then update its contents
        {
            detailsPanel_->setParamValue(0, Ogre::StringConverter::toString(camera_->getDerivedPosition().x));
            detailsPanel_->setParamValue(1, Ogre::StringConverter::toString(camera_->getDerivedPosition().y));
            detailsPanel_->setParamValue(2, Ogre::StringConverter::toString(camera_->getDerivedPosition().z));
            detailsPanel_->setParamValue(4, Ogre::StringConverter::toString(camera_->getDerivedOrientation().w));
            detailsPanel_->setParamValue(5, Ogre::StringConverter::toString(camera_->getDerivedOrientation().x));
            detailsPanel_->setParamValue(6, Ogre::StringConverter::toString(camera_->getDerivedOrientation().y));
            detailsPanel_->setParamValue(7, Ogre::StringConverter::toString(camera_->getDerivedOrientation().z));
        }
    }
	*/


	/* Update correctly the fightManager CLEMENT, I NEED YOU*/
	fightManager_->update();

	/* Update rendering */
	theSun_->update();

	for(std::list<GameEntity>::iterator ge = objectEntities_.begin() ; ge != objectEntities_.end() ; ge++)
	{
		(*ge).update(evt);
	}

	for(std::list<RobotEntity>::iterator re = robotsEntities_.begin() ; re != robotsEntities_.end() ; re++)
	{
		(*re).update(evt);
	}

    return true;
}

bool FightWindow::keyPressed(const OIS::KeyEvent &arg)
{
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	context.injectKeyDown((CEGUI::Key::Scan)arg.key);
	context.injectChar((CEGUI::Key::Scan)arg.text);
	return true;
}

bool FightWindow::keyReleased(const OIS::KeyEvent &arg)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);
	return true;
}

bool FightWindow::mouseMoved(const OIS::MouseEvent &arg)
{
	CEGUI::GUIContext &sys = CEGUI::System::getSingleton().getDefaultGUIContext();
	sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	// Scroll wheel.
	if (arg.state.Z.rel)
		sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
	return true;
}

bool FightWindow::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
	return true;
}

bool FightWindow::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
	return true;
}

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}