#include "TryWindow.h"

using namespace Ogre;
using namespace std;

TryWindow::TryWindow(void)
{
	fightManager_ = new FightManager("essai2.txt");
}

TryWindow::~TryWindow(void)
{
}

void TryWindow::createScene(void)
{
	//======== ABOUT LIGHT =========
	// -- The sun -- //
	sceneMgr_->setAmbientLight(Ogre::ColourValue(0.9f, 0.85f, 0.85f));
	sceneMgr_->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

	sunLight = sceneMgr_->createLight("SunLight");
	sunLight->setDiffuseColour(1.0, 1.0, 0.8f);
	sunLight->setSpecularColour(1.0, 1.0, 0.8f);

	sunLight->setType(Light::LT_SPOTLIGHT);
	sunLight->setDirection(Vector3(0, 0, 0));
	sunLight->setPosition(Vector3(-1000, 10000, 0));
	sunLight->setSpotlightRange(Degree(45), Degree(50));

	sunEntity = sceneMgr_->createEntity("sphere.mesh");
	sceneMgr_->getRootSceneNode()->createChildSceneNode(sunLight->getPosition())->attachObject(sunEntity);


	//======ABOUT THE CAMERA=======
	camera_->setPosition(100.0, 100.0, 100.0);


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
				DecorEntities.push_back(decorEntity);
			}
		}
	}
}

void TryWindow::createCamera()
{
	camera_ = sceneMgr_->createCamera("PlayerCam");
	camera_->setPosition(Ogre::Vector3(0, 300, 500));
	camera_->lookAt(Ogre::Vector3(0, 0, 0));

	camera_->setNearClipDistance(5);
	cameraMan_ = new OgreBites::SdkCameraMan(camera_);

}

void TryWindow::createViewports()
{
	Ogre::Viewport* vp = window_->addViewport(camera_);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	camera_->setAspectRatio(
		  Ogre::Real(vp->getActualWidth()) /
		  Ogre::Real(vp->getActualHeight()));
}

/* Gaming Loop */
bool TryWindow::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(window_->isClosed())
        return false;

    if(shutDown_)
        return false;

    // Need to capture/update each device
    keyboard_->capture();
    mouse_->capture();

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

	/* Update correctly the fightManager CLEMENT, I NEED YOU*/
	fightManager_->update();

	Vector3 pos = sunLight->getPosition();
	sunLight->setPosition(pos.x + 5, pos.y, pos.z);

    return true;
}