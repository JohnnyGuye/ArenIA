#include "LogoScene.h"

#include "GUIShowLogo.h"


LogoScene::LogoScene(Ogre::RenderWindow* window, Ogre::Root* root)
	: Scene(window, root),
	showLogos_(nullptr)
{
	sceneMgr_ = root_->createSceneManager(Ogre::ST_GENERIC);
}


LogoScene::~LogoScene(void)
{
	if(showLogos_)	delete showLogos_;
}

Scene::Scenes LogoScene::nextScene() const
{
	return FIGHT;
}

bool LogoScene::loadResources(void)
{
	return true;
}

bool LogoScene::launch(void)
{
	//Cameras
	camera_ = sceneMgr_->createCamera("PlayerCam");
	camera_->setPosition(Ogre::Vector3(0, 300, 500));
	camera_->lookAt(Ogre::Vector3(0, 0, 0));
	camera_->setNearClipDistance(5);

	//Viewports
	Ogre::Viewport* vp = window_->addViewport(camera_);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	showLogos_ = new GUIShowLogo(vp, "dec_all");

	camera_->setAspectRatio(
		  Ogre::Real(vp->getActualWidth()) /
		  Ogre::Real(vp->getActualHeight()));

	return true;
}

bool LogoScene::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return showLogos_->frameRenderingQueued(evt);
}

//------------------------------------------------------------------------------------------
bool LogoScene::keyPressed( const OIS::KeyEvent& arg)
{
    return true;
}

//---------------------------------------------------------------------------
bool LogoScene::keyReleased(const OIS::KeyEvent &arg)
{
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