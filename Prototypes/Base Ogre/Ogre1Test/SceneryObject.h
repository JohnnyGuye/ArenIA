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
* I guess i will create on my own a tileset with the good celltypes for a real accordance
* between what Tiled shows, and what you get in the game.
*/

#include "gameobject.h"

class SceneryObject : public GameObject
{
public:
	SceneryObject(Ogre::Vector3 position = Ogre::Vector3::ZERO, std::string name = "");
	virtual ~SceneryObject(void);

	virtual std::string getType() const;

protected:
	std::string cellType;
};

