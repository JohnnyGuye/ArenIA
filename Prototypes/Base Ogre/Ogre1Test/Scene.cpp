#include "Scene.h"


Scene::Scene(Ogre::RenderWindow* window, Ogre::Root* root)
	: window_(window),
	root_(root),
	sceneMgr_(nullptr)
{
}

Scene::~Scene(void)
{
	if(sceneMgr_)	root_->destroySceneManager(sceneMgr_);
}

Ogre::SceneManager* Scene::getSceneManager(void) const
{
	return sceneMgr_;
}
