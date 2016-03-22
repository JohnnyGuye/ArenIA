#include "Robot.h"

#include <Ogre.h>
#include <string>
#include <vector>

#include "GameObject.h"
#include "Stats.h"
//#include "Ability.h"

using namespace Ogre;
using namespace std;

/*
 action_ modifying methods
*/


Robot::Robot()
    :team_(NONE),
	stats_(),
	additionalStats_(),
	GameObject(),
	action_(IDLE),
	iaFilename_("EMPTY"),
	orientation_(Vector3::UNIT_X),
	turretOrientation_(Vector3::UNIT_X)
{
	setStatus();
}

Robot::~Robot()
{
}

bool Robot::resetAction()
{
    action_ = Robot::IDLE;
    return true; 
}

void Robot::update()
{

}

bool Robot::fire()
{
    //Something happens here to make the actual shooting
    action_ = action_ | SHOOTING;
    return true;
}

bool Robot::move()
{
    double speed = getSpeed();
    GameObject::move(Real(speed) * orientation_);
    action_ = action_ | MOVING;
    return true;
}

bool Robot::turnTurret (Ogre::Degree angle)
{
    //conversion for the quaternion's constructor (Degrees are more intuitive to use)
    Radian rotation(angle);
    Quaternion newDirection(angle, FORWARD_DEFAULT);
    turretOrientation_ = (newDirection * turretOrientation_).normalise();
	action_ = action_ | TURNING_TURRET;
    return true;
}

bool Robot::turnDirection (Ogre::Degree angle)
{
    //conversion for the quaternion's constructor (Degrees are more intuitive to use)
	GameObject::setOrientation(angle);
    Quaternion newDirection(angle, FORWARD_DEFAULT);
    orientation_ = (newDirection * orientation_).normalise();
	action_ = action_ | TURNING_WHEELS;
	return true;
}



/*
Ability-based Methods
*/
/*
bool useAbility(int idxAbility){
    //Something like return abilities_[idxAbility].run()
    return false //no actual effects for now
}

vector<Ability*> getKnownCompetences(Robot & robot){
    return robot.abilities_;
}

int addAbility(Ability* anAbility){
    abilities_.push_back(anAbility);
    return abilities_.size() - 1;//returns the index of the Ability insert
}

bool removeAbility(int idxAbility){
    abilities_.pop(idxAbility);
}
*/
/*
Basic Getters
*/

Degree Robot::getWheelAngle() const
{
	return Degree(orientation_.angleBetween(Vector3(Vector3::UNIT_X)));
}

Degree Robot::getTurretAngle() const
{
	return Degree(turretOrientation_.angleBetween(orientation_));
}

Vector3 Robot::getWheelOrientation() const
{
    return orientation_;
}

Vector3 Robot::getTurretOrientation() const
{
    return turretOrientation_;
}

double Robot::getSpeed() const
{
    return stats_.getSpeed() + additionalStats_.getSpeed();
}

Team Robot::getTeam() const
{
	return team_;
}

int Robot::getAction() const
{
	return action_;
}

bool Robot::isMoving() const
{
	return action_ == MOVING;
}

bool Robot::isShooting() const
{
	return action_ == SHOOTING;
}

bool Robot::isIDLE() const
{
	return (action_ == IDLE);
}


/*
Constructors & Destructors
*/
