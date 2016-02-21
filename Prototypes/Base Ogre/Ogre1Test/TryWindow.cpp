#include "TryWindow.h"

//---------------------------------------------------------------------------
TryWindow::TryWindow(void)
{
	fightManager_ = new FightManager();
}
//---------------------------------------------------------------------------
TryWindow::~TryWindow(void)
{
}

//---------------------------------------------------------------------------
void TryWindow::createScene(void)
{
	//========ABOUT LIGHT=========
	//Adding ambient light to the scene manager
    //mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));

	sceneMgr_->setAmbientLight(Ogre::ColourValue(0.9f, 1, 1));
	sceneMgr_->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
	
	//Add a second light
	//Ogre::Light* light = mSceneMgr->createLight("MainLight");
	//light->setPosition(20, 200, 50);

	Ogre::Light* spotLight = sceneMgr_->createLight("SpotLight");
	spotLight->setDiffuseColour(0, 0, 1.0);
	spotLight->setSpecularColour(0, 0, 1.0);
	spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
	spotLight->setDirection(camera_->getDirection());
	spotLight->setPosition(camera_->getPosition());
	spotLight->setSpotlightRange(Ogre::Degree(45), Ogre::Degree(50));


	//======ABOUT THE CAMERA=======
	camera_->setPosition(100.0, 100.0, 100.0);


	//========THE GROUND=========
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	
	Ogre::MeshManager::getSingleton().createPlane(
	  "ground",
	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  plane, 
	  2000, 2000, 40, 40, 
	  true, 
	  1, 5, 5, 
	  Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = sceneMgr_->createEntity("ground");
	sceneMgr_->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Rockwall");

	//========CREATE ENTITIES FROM TERRAIN===========
	GameObject*** grille = fightManager_->getTerrain()->getGrille();
	unsigned int width = fightManager_->getTerrain()->getWidth();
	unsigned int height = fightManager_->getTerrain()->getHeight();

	for(unsigned int i = 0; i < width; i++)
	{
		for(unsigned int j = 0; j < height; j++)
		{
			//	if(grille[i][j]->getName() != "0")
			{
				Ogre::Entity* decorEntity;
				Ogre::SceneNode* node;
				decorEntity = sceneMgr_->createEntity("knot.mesh");
				//node = sceneMgr_->getRootSceneNode()->createChildSceneNode(grille[i][j]->getPosition());
				node = sceneMgr_->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(i * 100.0, 0.0, j * 100));
				node->attachObject(decorEntity);
				DecorEntities.push_back(decorEntity);
			}
		}
	}
}

//---------------------------------------------------------------------------
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

    return true;
}