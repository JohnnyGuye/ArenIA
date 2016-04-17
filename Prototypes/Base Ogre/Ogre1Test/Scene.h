#pragma once

#include <OGRE\Ogre.h>

class Scene
{
public:
	Scene(void);
	virtual ~Scene(void);
	
	virtual bool setup(Ogre::Root* root) = 0;
};

