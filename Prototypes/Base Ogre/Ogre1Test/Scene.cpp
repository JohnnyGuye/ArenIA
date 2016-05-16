#include "Scene.h"

Scene::Scene(void)
	: root_(Ogre::Root::getSingletonPtr()),
	sceneMgr_(nullptr),
	camera_(nullptr),
	resourcesState_(NOT_LOADED),
	stop_(false),
	shutDown_(false)
{
	window_ = root_->getAutoCreatedWindow();
	silverback_ = Gorilla::Silverback::getSingletonPtr();
}

void Scene::loadResources(void)
{
	resourcesState_ = LOADING;
	_loadResources();
	resourcesState_ = LOADED;
}

Scene::~Scene(void)
{
}

Ogre::SceneManager* Scene::getSceneManager(void) const
{
	return sceneMgr_;
}
