#pragma once

/*
* This source file is a part of the 
*           ______                                  ___   ______
*          /      |                                |   | |      \
*         /       |                                |   | |       \
*        /        |                                |   | |        \
*       /    /|   |  ______     _______   __   __  |   | |   |\    \
*      /    / |   | |      \   |   ____| |  \ |  | |   | |   | \    \
*     /    /__|   | |  |)   |  |  |__    |   \|  | |   | |   |__\    \
*    /    ____    | |      /   |   __|   |       | |   | |    ___     \
*   /    /    |   | |   _  \   |  |      |       | |   | |   |    \    \
*  /    /     |   | |  | \  \  |  |____  |  |\   | |   | |   |     \    \
* /____/      |___| |__|  \__\ |_______| |__| \__| |___| |___|      \____\ project
* 
* Copyright (c) 2016-2017
*
* @author Johnny Guye
* @summary : This class is an object representing a wall. The only interaction you have
* with it is a possible collision. The cellType is usefull for creating the good interactions.
*/

#include "gameobject.h"

class SceneryObject : public GameObject
{
public:
	SceneryObject(Ogre::Vector3 position = Ogre::Vector3::ZERO, const int& num = 0);
	virtual ~SceneryObject(void);

	virtual int getType() const;

protected:
	int cellType;
};

