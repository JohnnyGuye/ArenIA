#include "MowerRobot.h"
#include "AbilityMissile.h"


MowerRobot::MowerRobot(Ogre::Vector3 position, std::string name, Team team)
	:	Robot(position, name, team)
{
	stats_ = Stats( Gauge(), Gauge(400), 60, 500, 0, 4.0);
	setTurretAbility(new AbilityMissile(this));
}


MowerRobot::~MowerRobot(void)
{
}

std::string MowerRobot::getTurretMesh() const
{
	return "RobotTondeuse.mesh";
}

Ogre::Real MowerRobot::getScale() const
{
	return 10;
}