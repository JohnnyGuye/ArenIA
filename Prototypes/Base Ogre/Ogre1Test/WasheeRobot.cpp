#include "WasheeRobot.h"
#include "AbilityMissile.h"


WasheeRobot::WasheeRobot(Ogre::Vector3 position, std::string name, Team team)
	:	Robot(position, name, team)
{
	stats_ = Stats( Gauge(), Gauge(600, 0, 600), 60, 500, 0, 4.0);
	setTurretAbility(new AbilityMissile(this));
}


WasheeRobot::~WasheeRobot(void)
{
}

std::string WasheeRobot::getTurretMesh() const
{
	return "RobotLaveLinge.mesh";
}

Ogre::Real WasheeRobot::getScale() const
{
	return 10;
}

Robot::Type WasheeRobot::getType() const
{
	return LAVE_LINGE;
}