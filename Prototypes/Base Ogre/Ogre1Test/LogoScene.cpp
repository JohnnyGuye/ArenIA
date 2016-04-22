#include "LogoScene.h"

#include "GUIShowLogo.h"

using namespace Ogre;


LogoScene::LogoScene(void)
	: Scene(),
	showLogos_(nullptr)
{
	sceneMgr_ = root_->createSceneManager(Ogre::ST_GENERIC);
}

LogoScene::~LogoScene(void)
{
}

void LogoScene::destroyScene(void)
{
	if(showLogos_)	delete showLogos_;
	sceneMgr_->clearScene();
	sceneMgr_->destroyCamera(camera_);
}

Scene::Scenes LogoScene::nextScene() const
{
	return FIGHT;
}

void LogoScene::_loadResources(void)
{
}

bool LogoScene::launch(void)
{
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

	showLogos_ = new GUIShowLogo(vp);

	camera_->setAspectRatio(
		  Ogre::Real(vp->getActualWidth()) /
		  Ogre::Real(vp->getActualHeight()));

	return true;
}

bool LogoScene::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(evt.timeSinceLastFrame > 0.5)
	{
		root_->clearEventTimes();
		return true;
	}
	if( stop_ )		
		return false;
	if( !showLogos_->frameRenderingQueued(evt))	
		return false;
	return true;
}

//------------------------------------------------------------------------------------------
bool LogoScene::keyPressed( const OIS::KeyEvent& arg)
{
    return true;
}
//---------------------------------------------------------------------------
bool LogoScene::keyReleased(const OIS::KeyEvent &arg)
{
	stop_ = true;
    return true;
}
//---------------------------------------------------------------------------
bool LogoScene::mouseMoved(const OIS::MouseEvent &arg)
{
    return true;
}
//---------------------------------------------------------------------------
bool LogoScene::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    return true;
}
//---------------------------------------------------------------------------
bool LogoScene::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    return true;
}