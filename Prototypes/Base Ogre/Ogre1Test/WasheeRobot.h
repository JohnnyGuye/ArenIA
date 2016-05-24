#pragma once
#include "robot.h"
class WasheeRobot :
	public Robot
{
public:
	WasheeRobot(Ogre::Vector3 position = Ogre::Vector3::ZERO, std::string name = "", Team team = NONE);
	virtual ~WasheeRobot(void);

	virtual Type getType() const;
	virtual std::string getTurretMesh() const;
	virtual Ogre::Real getScale() const;
};

