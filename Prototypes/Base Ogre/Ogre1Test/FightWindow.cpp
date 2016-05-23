#include "FightWindow.h"


#include <cstdlib>
#include "FightScene.h"
#include "LogoScene.h"
#include "CodeEditScene.h"
#include "LauncherScene.h"

using namespace Ogre;
using namespace std;

// ------------------------------------------------------------
// ------------ THE FIGHT WINDOW ------------------------------
// ------------------------------------------------------------
bool FightWindow::alt_(false);
bool FightWindow::lctrl_(false);
bool FightWindow::rctrl_(false);
bool FightWindow::lshift_(false);
bool FightWindow::rshift_(false);

FightWindow::FightWindow(void)
	:  root_(nullptr),
    window_(nullptr),
    resourcesCfg_(Ogre::StringUtil::BLANK),
    pluginsCfg_(Ogre::StringUtil::BLANK),
    cursorWasVisible_(false),
    shutDown_(false),
    inputManager_(nullptr),
    mouse_(nullptr),
    keyboard_(nullptr),
	activScene_(nullptr)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

FightWindow::~FightWindow(void)
{
	for(SceneMap::iterator it = sceneMap_.begin(); it != sceneMap_.end() ; it++)
	{
		if(it->second)	delete it->second;
	}
	if(root_)	delete root_;
}
//---------------------------------------------------------------------------
void FightWindow::go(void)
{
#ifdef _DEBUG
#ifndef OGRE_STATIC_LIB
    resourcesCfg_ = m_ResourcePath + "resources_d.cfg";
    pluginsCfg_ = m_ResourcePath + "plugins_d.cfg";
#else
    resourcesCfg_ = "resources_d.cfg";
    pluginsCfg_ = "plugins_d.cfg";
#endif
#else
#ifndef OGRE_STATIC_LIB
    resourcesCfg_ = m_ResourcePath + "resources.cfg";
    pluginsCfg_ = m_ResourcePath + "plugins.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif
#endif

    if (!setup())
        return;

    root_->startRendering();
}
//---------------------------------------------------------------------------
bool FightWindow::setup(void)
{
    root_ = new Ogre::Root(pluginsCfg_);

	//Initialize angles translations
	LogManager::getSingletonPtr()->logMessage("*** Initializing resource path ***");
    setupResources();

	LogManager::getSingletonPtr()->logMessage("*** Window ***");
	if (!root_->showConfigDialog())	return false;

	window_ = root_->initialise(true, "ArenIA");
	
	//Creation of the scenes
	sceneMap_.insert(ScenePair("Logos", new LogoScene()));	//Logos at beginning
	sceneMap_.insert(ScenePair("Fight", new FightScene()));	//Real game
	sceneMap_.insert(ScenePair("Code", new CodeEditScene()));	//Coding instance
	sceneMap_.insert(ScenePair("Launcher", new LauncherScene()));	//Launch the game

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Popular");
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
	activScene_ = sceneMap_.at("Launcher");
	activScene_->loadResources();
	
	FightScene* fightScene = (FightScene*)sceneMap_.at("Fight");
	fightScene->initFightManager("1v1.txt");
	
	activScene_->launch();

    createFrameListener();

    return true;
};
//---------------------------------------------------------------------------
void FightWindow::setupResources(void)
{

    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(resourcesCfg_);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app.
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location.
            if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative directories
                archName = Ogre::String(Ogre::macBundlePath() + "/" + archName);
#endif

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//---------------------------------------------------------------------------
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

	root_->addFrameListener(this);

	windowResized(window_);
}
//---------------------------------------------------------------------------
bool FightWindow::changeScene()
{
	Scene::Scenes nextScene = activScene_->nextScene();
	activScene_->destroyScene();
	switch(nextScene)
	{
	case Scene::EXIT:
		shutDown_ = true;
		return false;
		break;
	case Scene::LAUNCHER:
		activScene_ = sceneMap_.at("Launcher");
		break;
	case Scene::LOGO:
		activScene_ = sceneMap_.at("Logo");
	case Scene::FIGHT:
	default:
		activScene_ = sceneMap_.at("Fight");
		break;
	}

	activScene_->loadResources();
	activScene_->launch();
	return true;
}
//---------------------------------------------------------------------------
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

	if(!activScene_->frameRenderingQueued(evt))
	{
		return changeScene();
	}

    return true;
}
//---------------------------------------------------------------------------
bool FightWindow::keyPressed( const OIS::KeyEvent& arg)
{
	switch(arg.key)
	{
	case OIS::KC_LSHIFT:	lshift_ = true; break;
	case OIS::KC_RSHIFT:	rshift_ = true; break;
	case OIS::KC_LCONTROL:	lctrl_ = true;	break;
	case OIS::KC_RCONTROL:	rctrl_ = true;	break;
	case OIS::KC_LMENU:		alt_ = true;	break;
	case OIS::KC_F12:
		shutDown_ = isAlt();	
		break;
	default:
		break;
	}
	if(!activScene_->keyPressed(arg))
		shutDown_ = true;
    return true;
}
//---------------------------------------------------------------------------
bool FightWindow::keyReleased(const OIS::KeyEvent &arg)
{
	switch(arg.key)
	{
	case OIS::KC_LSHIFT:	lshift_ = false; break;
	case OIS::KC_RSHIFT:	rshift_ = false; break;
	case OIS::KC_LCONTROL:	lctrl_ = false;	break;
	case OIS::KC_RCONTROL:	rctrl_ = false;	break;
	case OIS::KC_LMENU:		alt_ = false;	break;
	default:
		break;
	}
    activScene_->keyReleased(arg);
    return true;
}
//---------------------------------------------------------------------------
bool FightWindow::mouseMoved(const OIS::MouseEvent &arg)
{
	activScene_->mouseMoved(arg);
    return true;
}
//---------------------------------------------------------------------------
bool FightWindow::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    activScene_->mousePressed(arg, id);
    return true;
}
//---------------------------------------------------------------------------
bool FightWindow::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    activScene_->mouseReleased(arg, id);
    return true;
}
//---------------------------------------------------------------------------
bool FightWindow::isShift()	{	return (lshift_ | rshift_);	}
bool FightWindow::isAlt()	{	return alt_;	}
bool FightWindow::isCtrl()	{	return (lctrl_ | rctrl_);	}
//---------------------------------------------------------------------------
// Adjust mouse clipping area
void FightWindow::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mouse_->getMouseState();
    ms.width = width;
    ms.height = height;
}
//---------------------------------------------------------------------------
// Unattach OIS before window shutdown (very important under Linux)
void FightWindow::windowClosed(Ogre::RenderWindow* rw)
{
    // Only close for window that created OIS (the main window in these demos)
    if(rw == window_)
    {
        if(inputManager_)
        {
            inputManager_->destroyInputObject(mouse_);
            inputManager_->destroyInputObject(keyboard_);

            OIS::InputManager::destroyInputSystem(inputManager_);
            inputManager_ = 0;
        }
    }
}