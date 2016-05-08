#include "FightScene.h"

using namespace std;
using namespace Ogre;

FightScene::FightScene(void)
	: Scene(),
	fightManager_(nullptr),
	state_(COUNTDOWN),
	theSun_(nullptr),
	pause_(true),
	console_(nullptr),
	decompte_(nullptr),
	hud_(nullptr),
	cameraMan_(nullptr),
	lag_(0),
	displaySpeed_(1)
{
	sceneMgr_ = root_->createSceneManager(ST_GENERIC);
}
//---------------------------------------------------------------------------
FightScene::~FightScene(void)
{
}
//---------------------------------------------------------------------------
void FightScene::destroyScene(void)
{
	//delete logic first
	if(fightManager_) delete fightManager_;	

	//destroy GUI
	if(hud_)		delete hud_;
	if(console_)	delete console_;
	if(decompte_)	delete decompte_;

	//destroy entities
	if(theSun_)		delete theSun_;
	for(unsigned int i = 0; i < DecorEntities_.size(); i++)
	{
		delete DecorEntities_[i];
	}
	sceneMgr_->clearScene();
	sceneMgr_->destroyCamera(camera_);
	if(cameraMan_)	delete cameraMan_;
}
//---------------------------------------------------------------------------
bool FightScene::initFightManager(const std::string& map)
{
	if(fightManager_)	return false;
	fightManager_ = new FightManager(map);
	return true;
}
//---------------------------------------------------------------------------
Scene::Scenes FightScene::nextScene() const
{
	return EXIT;
}
//---------------------------------------------------------------------------
void FightScene::_loadResources(void)
{
	ResourceGroupManager::getSingleton().initialiseResourceGroup("Game");
}
//---------------------------------------------------------------------------
bool FightScene::launch(void)
{
	LogManager::getSingletonPtr()->logMessage("*** Cameras ***");
	//Cameras
	camera_ = sceneMgr_->createCamera("PlayerCam");
	camera_->setPosition(Vector3(0, 300, 500));
	camera_->lookAt(Vector3(0, 0, 0));
	camera_->setNearClipDistance(5);
	cameraMan_ = new OgreBites::SdkCameraMan(camera_);
	cameraMan_->setTopSpeed(Real(2000));

	LogManager::getSingletonPtr()->logMessage("*** Viewports ***");
	//Viewports
	Viewport* vp;
	try
	{
		vp = window_->getViewportByZOrder(0);
		vp->setCamera(camera_);
	}
	catch(Exception e)
	{
		vp = window_->addViewport(camera_);
	}
	
	vp->setBackgroundColour(ColourValue(0, 0, 0));

	decompte_ = new GUIDecompte(vp, "dec_all");
	hud_ = new HUD(vp, fightManager_);
	console_ = new GUIConsole(vp);
	hud_->init();

	camera_->setAspectRatio(
		  Real(vp->getActualWidth()) /
		  Real(vp->getActualHeight()));

	createScene();
	return true;
}
//---------------------------------------------------------------------------
void FightScene::createScene(void)
{
	//======== ABOUT LIGHT =========
	// -- The sun -- //
	theSun_ = new Sun(this);
	//sceneMgr_->setSkyBox(true, "Examples/SpaceSkyBox");
	//sceneMgr_->setSkyBox(true, "Arenia/Skybox", 3000.f, false);

	//======ABOUT THE CAMERA=======
	camera_->setPosition(
		fightManager_->getTerrain()->getWidth() * 50.0f, 
		500.0f, 
		fightManager_->getTerrain()->getHeight() * 50.0f
		);
	
	createRobots();

	//========THE GROUND=========
	Plane plane(Vector3::UNIT_Y, 0);
	
	MeshManager::getSingleton().createPlane(
	  "ground",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  plane, 
	  fightManager_->getTerrain()->getWidth() * Terrain::CELL_SIZE, fightManager_->getTerrain()->getHeight() * Terrain::CELL_SIZE, 10, 10, 
	  true, 
	  1, 5.0f, 5.0f, 
	  Vector3::UNIT_X);

	Vector3 offset(fightManager_->getTerrain()->getWidth() * Terrain::CELL_SIZE * 0.5f, 
		0, 
		fightManager_->getTerrain()->getHeight() * Terrain::CELL_SIZE * 0.5f);

	Entity* groundEntity = sceneMgr_->createEntity("ground");
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
				Degree		yaw(Real(0));
				Vector3		offset(Terrain::CELL_SIZE * 0.5, 0, Terrain::CELL_SIZE * 0.5);
				std::string mesh;

				switch(so->getType())
				{	
				case 1:
					yaw += Degree(90);
				case 3:
					yaw += Degree(90);
				case 35:
					yaw += Degree(90);
				case 33:
					yaw += Degree(90);
					mesh = "Wall_corner.mesh";
					break;
				case 17:
				case 19:
					yaw += Degree(90);
				case 2:
				case 4:
				case 5:
				case 6:
				case 20:
				case 21:
				case 22:
				case 34:
				case 36:
				case 37:
				case 38:
					mesh = "Wall_basic.mesh";
					offset.y = Terrain::CELL_SIZE * 0.4;	//Caprice, i just want different height of walls
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
				node->roll(yaw);
				DecorEntities_.push_back(decorEntity);
			}
		}
	}
}
//---------------------------------------------------------------------------
bool FightScene::frameRenderingQueued(const FrameEvent& evt)
{
	if(evt.timeSinceLastFrame > 0.25)
	{
		root_->clearEventTimes();
		return true;
	}
	cameraMan_->frameRenderingQueued(evt);
	if(state_ == COUNTDOWN)	
	{	
		if(!decompte_->frameRenderingQueue(evt))
		{
			pause_ = false;
			state_ = GAME;	
		}
	}
	
	if(!pause_)
	{
		/* LOGIC */
		for(lag_ += (evt.timeSinceLastFrame * 1000 * 1000 * displaySpeed_) ; 
			lag_ >= (GameTime::ROUND_IN_MS) ; 
			lag_ -= (GameTime::ROUND_IN_MS))
		{
			fightManager_->update();
		}
	
		/* RENDERING */
		theSun_->update();

		for(Missile * m = fightManager_->renderLastQueuedMissile() ;
			m != nullptr ; 
			m = fightManager_->renderLastQueuedMissile())
		{
			addMissile(m);
		}

		for(auto ge = objectEntities_.begin() ; ge != objectEntities_.end() ; ge++)
		{
			(*ge).update(evt);
		}
		

		for(auto re = robotsEntities_.begin() ; re != robotsEntities_.end() ; re++)
		{
			(*re).update(evt);
		}

		for(auto me = missileEntities_.begin() ; me != missileEntities_.end() ;)
		{
			auto m = *me;
			if(!m.update(evt))
			{
				me = missileEntities_.erase(me);
			}
			else
			{
				me++;
			}
		}

		

		console_->frameStarted(evt);
		hud_->frameRenderingQueued(evt);
	}

	
	return true;
}
//---------------------------------------------------------------------------
bool FightScene::keyPressed( const OIS::KeyEvent& arg)
{
	switch(state_)
	{
	case GAME:
		cameraMan_->injectKeyDown(arg);
		switch(arg.key)
		{
		case OIS::KC_F2:
			{
				MaterialManager::getSingleton().setDefaultTextureFiltering(TFO_BILINEAR);
				MaterialManager::getSingleton().setDefaultAnisotropy(1);
			}
			break;
		case OIS::KC_F3:
			{
				String newVal;
				PolygonMode pm;

				switch (camera_->getPolygonMode())
				{
				case PM_SOLID:
					newVal = "Wireframe";
					pm = PM_WIREFRAME;
					break;
				case PM_WIREFRAME:
				default:
					newVal = "Solid";
					pm = PM_SOLID;
				}

				camera_->setPolygonMode(pm);
			}
			break;
		case OIS::KC_SUBTRACT:
			if(displaySpeed_ > 0.25) displaySpeed_ *= 0.5;
			break;
		case OIS::KC_ADD:
			if(displaySpeed_ < 16) displaySpeed_ *= 2;
			break;
		case OIS::KC_SYSRQ:
			window_->writeContentsToTimestampedFile("screenshot", ".jpg");
			break;
		case OIS::KC_PAUSE:
			pause_ = !pause_;
			break;
		}
	case CONSOLE_ON:
		console_->onKeyPressed(arg);
		break;

	}
    if (arg.key == OIS::KC_ESCAPE)
    {
        return false;
    }
	else if (arg.key == OIS::KC_F1)
	{
		if(state_ != COUNTDOWN)
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
		
	}
 
    return true;
}
//---------------------------------------------------------------------------
bool FightScene::keyReleased(const OIS::KeyEvent &arg)
{
    cameraMan_->injectKeyUp(arg);
    return true;
}
//---------------------------------------------------------------------------
bool FightScene::mouseMoved(const OIS::MouseEvent &arg)
{
	switch(state_)
	{
	case CONSOLE_ON:
		break;
	case GAME:
	default:
		cameraMan_->injectMouseMove(arg);
		break;
	}
    return true;
}
//---------------------------------------------------------------------------
bool FightScene::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    cameraMan_->injectMouseDown(arg, id);
    return true;
}
//---------------------------------------------------------------------------
bool FightScene::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    cameraMan_->injectMouseUp(arg, id);
    return true;
}
// ----------------------------------------------
// ---------------- THE SUN ---------------------
// ----------------------------------------------

FightScene::Sun::Sun(FightScene* fs)
	: fs_(fs), 
	sceneMgr_(fs->sceneMgr_),
	offset_(fs_->fightManager_->getTerrain()->getDimension())
{
	//Entity and position
	Vector3 initPos = Vector3(Real(ORBIT), 0.f, 500.f);
	node_ = sceneMgr_->getRootSceneNode()->createChildSceneNode(initPos);

	//Ambient light
	sceneMgr_->setAmbientLight(ColourValue(0.4f, 0.4f, 0.4f));
	sceneMgr_->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	
	//SpotLight
	light_ = sceneMgr_->createLight("SunLight");
	light_->setDiffuseColour(0.95f, 0.85f, 0.95f);
	light_->setSpecularColour(0.7f, 0.65f, 0.7f);

	light_->setType(Light::LT_POINT);
	light_->setDirection(Vector3::ZERO);
	light_->setPosition(initPos);
}

FightScene::Sun::~Sun()
{
}

void FightScene::Sun::update()
{
	Real dayRatio(fs_->fightManager_->getDayRatio());
	Real cos = Math::Cos(Math::PI * dayRatio);
	Real sin = Math::Sin(Math::PI * dayRatio);
	node_->setPosition( cos * ORBIT + offset_.y, sin* ORBIT, offset_.x); 
	light_->setPosition(node_->getPosition());
	Real r(abs(2.f * dayRatio - 1.f) * .4f + .6f);
	Real v(0.6f);
	Real b(abs(2.f * dayRatio - 1.f) * (-.5f) + 1.5f);
	Real s(abs(2.f * dayRatio - 1.f) * (-.3f) + 1.3f);
	light_->setDiffuseColour(r * s, v * s, b * s);
}

// ----------------------------------------------
// --------------- GAME ENTITY ------------------
// ----------------------------------------------

FightScene::GameEntity::GameEntity(FightScene* fs, const string& mesh,
	const Vector3& position, const Real& scale, GameObject* object)
	:	fs_(fs),
	object_(object),
	orientation_(0),
	animState_(nullptr)
{
	entity_ = fs->sceneMgr_->createEntity(mesh); 

	node_ = fs->sceneMgr_->getRootSceneNode()->createChildSceneNode();
	node_->setPosition(position);
	node_->setScale(scale, scale, scale);
	node_->attachObject(entity_);
	node_->pitch(Degree(-90));

	if(entity_->hasAnimationState("IDLE"))
	{
		animState_ = entity_->getAnimationState("IDLE");
		animState_->setLoop(true);
		animState_->setEnabled(true);
	}
}

FightScene::GameEntity::~GameEntity()
{
	//fs_->sceneMgr_->destroyEntity(entity_);
	//fs_->sceneMgr_->destroySceneNode(node_);
}

bool FightScene::GameEntity::update(const FrameEvent& evt)
{
	if(object_->isDead()) return false;
	node_->setPosition(object_->getPosition());

	if(object_->getOrientation() != orientation_)
	{
		node_->roll(object_->getOrientation() - orientation_);
		orientation_ = object_->getOrientation();
	}

	if(animState_)	animState_->addTime(evt.timeSinceLastFrame);
	return true;
}

// ----------------------------------------------
// --------------- ROBOT ENTITY -----------------
// ----------------------------------------------

FightScene::RobotEntity::RobotEntity(FightScene* fs, const string& mesh,
	const Vector3& position, const Real& scale, Robot* robot)
	:	GameEntity(fs, mesh, position, scale, robot)
{
	
	robot->setOrientation(Degree(0));
	node_->roll(Degree(robot->getOrientation()));
}

FightScene::RobotEntity::~RobotEntity()
{
}

bool FightScene::RobotEntity::update(const FrameEvent& evt)
{
	Robot* robot = (Robot*)object_;
	animState_ = entity_->getAnimationState(stateToString(robot->getState()));
	return GameEntity::update(evt);
}

string FightScene::RobotEntity::stateToString(const Robot::State& state) const
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
// --------------- MISSILE ENTITY ---------------
// ----------------------------------------------

FightScene::MissileEntity::MissileEntity(FightScene* fs, const std::string& mesh, const Ogre::Real& scale, Missile* missile)
	:	GameEntity(fs, mesh, missile->getPosition(), scale, missile)
{
	//missile->setOrientation(Degree(0));
	node_->roll(Degree(missile->getOrientation()));
}

FightScene::MissileEntity::~MissileEntity()
{
}

bool FightScene::MissileEntity::update(const FrameEvent& evt)
{
	Missile* missile = (Missile*)object_;
	return GameEntity::update(evt);
}

// ----------------------------------------------
// --------------- CREATIONS --------------------
// ----------------------------------------------

void FightScene::createEntity(const string& mesh, const Vector3& position, const Real& scale)
{
	//Add some configuration
	objectEntities_.push_back(GameEntity(this, mesh, position, scale));
}

void FightScene::createRobot(const std::string& name, const Robot::Type& type, const Robot::Team& team, const Vector3& position, const Real& scale)
{
	string mesh;
	switch(type){
	case Robot::LAVE_LINGE:
		mesh = "RobotLaveLinge.mesh";
	default:
		mesh = "RobotLaveLinge.mesh";

	}
	Robot* robot = new Robot(position, name, team);
	robotsEntities_.push_back(RobotEntity(this, mesh, position, scale, robot));
	fightManager_->addRobot(robot);
}

void FightScene::addMissile(Missile* missile)
{
	std::string mesh = "RobotTondeuse_Projectile.mesh";
	Real scale(80);
	missileEntities_.push_back(MissileEntity(this, mesh, scale, missile));
	//std::cout << "Missile created" << std::endl;
}

void FightScene::createRobots(void)
{
	std::list<Robot*> robots = fightManager_->getRobots();

	for(std::list<Robot*>::iterator it = robots.begin(); it != robots.end() ; it++ )
	{
		Real scale;
		string mesh;
		Robot::Type type = Robot::TONDEUSE;
		switch(type)
		{
		case Robot::TONDEUSE:
			scale = 20;
			mesh = "RobotTondeuse.mesh";
			break;
		case Robot::LAVE_LINGE:
		default:
			scale = 10;
			mesh = "RobotLaveLinge.mesh";
		}
		robotsEntities_.push_back(RobotEntity(this, mesh, (*it)->getPosition(), scale, (*it)));
	}
}