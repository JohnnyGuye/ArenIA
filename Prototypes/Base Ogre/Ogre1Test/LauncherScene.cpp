#include "LauncherScene.h"
#include "GUILauncher.h"

using namespace Ogre;

LauncherScene::LauncherScene(void)
	: Scene(),
	GUILauncher_(nullptr),
	camera_(nullptr),
	fightInformations_(new FightInformations())
{
	fightInformations_->ai = Terrain::NOT_KNOWN;
	fightInformations_->robot = new WasheeRobot();
	fightInformations_->terrain = new Terrain("1v1.txt");
	sceneMgr_ = root_->createSceneManager(Ogre::ST_GENERIC);
}

LauncherScene::~LauncherScene(void)
{
	delete fightInformations_;
}

void LauncherScene::destroyScene(void)
{
	if(GUILauncher_)	delete GUILauncher_;
	sceneMgr_->clearScene();
	sceneMgr_->destroyCamera(camera_);
}

Scene::Scenes LauncherScene::nextScene() const
{
	if(shutDown_)
		return EXIT;
	return FIGHT;
}

FightInformations* LauncherScene::getFightInformations() const
{
	return fightInformations_;
}

void LauncherScene::_loadResources(void)
{
}

bool LauncherScene::launch(void)
{
	shutDown_ = false;
	stop_ = false;
	//Cameras
	camera_ = sceneMgr_->createCamera("PlayerCam");
	camera_->setPosition(Ogre::Vector3(0, 300, 500));
	camera_->lookAt(Ogre::Vector3(0, 0, 0));
	camera_->setNearClipDistance(5);

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
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	//INSERT GUI
	GUILauncher_ = new GUILauncher(vp, this);

	camera_->setAspectRatio(
		  Ogre::Real(vp->getActualWidth()) /
		  Ogre::Real(vp->getActualHeight()));

	return true;
}

bool LauncherScene::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(evt.timeSinceLastFrame > 0.5)
	{
		root_->clearEventTimes();
		return true;
	}

	if( stop_ )		
		return false;
	if( !GUILauncher_->frameRenderingQueued(evt))	
		return false;
	return true;
}
//------------------------------------------------------------------------------------------
bool LauncherScene::keyPressed( const OIS::KeyEvent& arg)
{
	switch(arg.key)
	{
	case OIS::KC_ESCAPE:
		stop_ = true;
		shutDown_ = true;
		break;
	default:
		break;
	}
    return true;
}
//---------------------------------------------------------------------------
bool LauncherScene::keyReleased(const OIS::KeyEvent &arg)
{
    return true;
}
//---------------------------------------------------------------------------
bool LauncherScene::mouseMoved(const OIS::MouseEvent &arg)
{
	GUILauncher_->mouseMoved(arg);
    return true;
}
//---------------------------------------------------------------------------
bool LauncherScene::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	GUILauncher_->mousePressed(arg, id);
    return true;
}
//---------------------------------------------------------------------------
bool LauncherScene::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	GUILauncher_->mouseReleased(arg, id);
    return true;
}