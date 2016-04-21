#include "Scene.h"

Scene::Scene(Ogre::RenderWindow* window, Ogre::Root* root)
	: window_(window),
	root_(root),
	sceneMgr_(nullptr),
	resourcesState_(NOT_LOADED)
{
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

void Scene::destroyScene(void)
{
}

Ogre::SceneManager* Scene::getSceneManager(void) const
{
	return sceneMgr_;
}
