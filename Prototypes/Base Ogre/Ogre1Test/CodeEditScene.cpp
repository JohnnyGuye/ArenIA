#include "CodeEditScene.h"

using namespace std;
using namespace Ogre;

CodeEditScene::CodeEditScene(void)
	: Scene()
{
	sceneMgr_ = root_->createSceneManager(ST_GENERIC);
}

CodeEditScene::~CodeEditScene(void)
{
}

void CodeEditScene::_loadResources(void)
{
}

bool CodeEditScene::launch()
{
	//Camera
	camera_ = sceneMgr_->createCamera("PlayerCam");
	camera_->setPosition(Vector3(0, 300, 500));
	camera_->lookAt(Vector3(0, 0, 0));
	camera_->setNearClipDistance(5);

	//Viewport
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
	
	GUICode_ = new GUICode(vp);
	vp->setBackgroundColour(ColourValue(0, 0, 0));

	camera_->setAspectRatio(
		  Real(vp->getActualWidth()) /
		  Real(vp->getActualHeight()));

	createScene();
	return true;
}

void CodeEditScene::createScene(void)
{

}

bool CodeEditScene::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(!GUICode_->frameRenderingQueued(evt))
		return false;
	return !stop_;
}

Scene::Scenes CodeEditScene::nextScene(void) const
{
	return EXIT;
}

void CodeEditScene::destroyScene()
{
}


bool CodeEditScene::keyPressed( const OIS::KeyEvent& arg)
{
	switch(arg.key)
	{
	case OIS::KC_ESCAPE:
		stop_ = true;
		break;
	default:
		break;
	}
    return true;
}
//---------------------------------------------------------------------------
bool CodeEditScene::keyReleased(const OIS::KeyEvent &arg)
{
    return true;
}
//---------------------------------------------------------------------------
bool CodeEditScene::mouseMoved(const OIS::MouseEvent &arg)
{

    return true;
}
//---------------------------------------------------------------------------
bool CodeEditScene::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    return true;
}
//---------------------------------------------------------------------------
bool CodeEditScene::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    return true;
}