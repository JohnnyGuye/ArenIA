#include "Scene.h"

Scene::Scene(void)
	: root_(Ogre::Root::getSingletonPtr()),
	sceneMgr_(nullptr),
	camera_(nullptr),
	resourcesState_(NOT_LOADED),
	stop_(false),
	shutDown_(false),
	nextScene_(Scene::EXIT)
{
	window_ = root_->getAutoCreatedWindow();
	silverback_ = Gorilla::Silverback::getSingletonPtr();
}

void Scene::loadResources(void)
{
	resourcesState_ = LOADING;
	_loadResources();
	resourcesState_ = LOADED;
	stop_ = false;
}

Scene::~Scene(void)
{
}

Ogre::SceneManager* Scene::getSceneManager(void) const
{
	return sceneMgr_;
}

void Scene::stop(Scene::Scenes nextScene)
{
	stop_ = true;
	nextScene_ = nextScene;
}