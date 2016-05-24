#pragma once
#include "robot.h"
class MowerRobot :
	public Robot
{
public:
	MowerRobot(Ogre::Vector3 position = Ogre::Vector3::ZERO, std::string name = "", Team team = NONE);
	virtual ~MowerRobot(void);

	virtual Type getType() const;
	virtual std::string getTurretMesh() const;
	virtual Ogre::Real getScale() const;
};

