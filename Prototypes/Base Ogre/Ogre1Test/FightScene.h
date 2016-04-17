#pragma once

#include "Scene.h"

class FightScene :
	public Scene
{
public:
	FightScene(void);
	virtual ~FightScene(void);

	virtual bool setup(Ogre::Root* root);
};

