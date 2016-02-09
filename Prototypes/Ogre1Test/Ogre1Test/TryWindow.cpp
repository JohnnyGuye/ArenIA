/*
-----------------------------------------------------------------------------
Filename:    TryWindow.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "TryWindow.h"

//---------------------------------------------------------------------------
TryWindow::TryWindow(void)
	:
	mDistance(0),
	mWalkSpd(70.0),
	mDirection(Ogre::Vector3::ZERO),
	mDestination(Ogre::Vector3::ZERO),
	mAnimationState(0),
	mEntity(0),
	mNode(0)
{
}
//---------------------------------------------------------------------------
TryWindow::~TryWindow(void)
{
}

//---------------------------------------------------------------------------
void TryWindow::createScene(void)
{

	// Pour voir les fonctionnalités de bases, mettez en commentaire ou non les blocks que vous voulez
	// Les lumières sont importantes donc il faut à minima en garder une pour garder du sens

	//========ABOUT LIGHT=========
	//Adding ambient light to the scene manager
    //mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.9f, 1, 1));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	
	//Add a second light
	//Ogre::Light* light = mSceneMgr->createLight("MainLight");
	//light->setPosition(20, 200, 50);

	Ogre::Light* spotLight = mSceneMgr->createLight("SpotLight");
	spotLight->setDiffuseColour(0, 0, 1.0);
	spotLight->setSpecularColour(0, 0, 1.0);
	spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
	spotLight->setDirection(mCamera->getDirection());
	spotLight->setPosition(mCamera->getPosition());
	spotLight->setSpotlightRange(Ogre::Degree(45), Ogre::Degree(50));


	//======ABOUT THE CAMERA=======
	mCamera->setPosition(90.0, 280.0, 535.0);
	mCamera->pitch(Ogre::Degree(-30.0));// Pour tourner. Y en a 3, pitch yaw et je sais plus quoi.
	mCamera->yaw(Ogre::Degree(-15.0));


	//============ROBOT============
	mEntity = mSceneMgr->createEntity("robot.mesh");
	// Ce fichier se charge de créer la forme dans le jeu, d'animer l'entité 
	// et récupère les textures dans un des fichiers média
 
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(
	  Ogre::Vector3(0, 0, 25.0));
		mNode->attachObject(mEntity);

	//Robot passage way
	Ogre::Entity* ent;
	Ogre::SceneNode* node;
 
	ent = mSceneMgr->createEntity("knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
	  Ogre::Vector3(0, 100.0, 25.0));
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);
 
	ent = mSceneMgr->createEntity("knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
	  Ogre::Vector3(550.0, 100.0, 50.0));
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);
 
	ent = mSceneMgr->createEntity("knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
	  Ogre::Vector3(-100.0, 100.0,-200.0));
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);

	mAnimationState = mEntity->getAnimationState("Idle");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);

	// J'ai déjà fait plus propre mais bon...
	mWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mWalkList.push_back(Ogre::Vector3(-100.0, 0, -200.0));
	mWalkList.push_back(Ogre::Vector3(0, 0, 25.0));
	
	//=========NINJA=======
	
	Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("ninja.mesh");
	ninjaEntity->setCastShadows(true);
 
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ninjaEntity);
	


	//========THE GROUND=========
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	
	Ogre::MeshManager::getSingleton().createPlane(
	  "ground",
	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  plane, 
	  1500, 1500, 20, 20, 
	  true, 
	  1, 5, 5, 
	  Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Rockwall");
	
}

//---------------------------------------------------------------------------
void TryWindow::createCamera()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0, 300, 500));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));

	mCamera->setNearClipDistance(5);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);

}

void TryWindow::createViewports()
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
		  Ogre::Real(vp->getActualWidth()) /
		  Ogre::Real(vp->getActualHeight()));
}


/* Gaming Loop */
bool TryWindow::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // If dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())          // If details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

	/* Exemple de déplacement d'un robot */

	if (mDirection == Ogre::Vector3::ZERO) 
	{
	  if (nextLocation())
	  {
		mAnimationState = mEntity->getAnimationState("Walk");//On anime le déplacement
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	  }
	}
	else
	{
	  Ogre::Real move = mWalkSpd * evt.timeSinceLastFrame;
	  mDistance -= move;
	  if (mDistance <= 0)
	  {
		mNode->setPosition(mDestination);
		mDirection = Ogre::Vector3::ZERO;
		if (!nextLocation())
		{
			mAnimationState = mEntity->getAnimationState("Idle");//On anime le mec qui idle sur place
			mAnimationState->setLoop(true);
			mAnimationState->setEnabled(true);
		}
	  }
	  else
		{
			mNode->translate(move * mDirection);
		}
	}

	/* Là on actualise l'animation */
	mAnimationState->addTime(evt.timeSinceLastFrame);

    return true;
}

bool TryWindow::nextLocation()
{
	if (mWalkList.empty())
		return false;
	mDestination = mWalkList.front();
	mWalkList.pop_front();
	mDirection = mDestination - mNode->getPosition();
	mDistance = mDirection.normalise();
	return true;
}