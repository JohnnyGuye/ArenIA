#include <Ogre.h>
#include <string>
#include <vector>
#include "GameObject.h"
#include "Stats.h"
//#include "Ability.h"
#include "Robot.h"

using namespace Ogre;
using namespace std;

/*
 action_ modifying methods
*/
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
    if ( !(action_ & Robot::SHOOTING)){
        //To avoid continuous fire toggling
        action_ += Robot::SHOOTING;
    }
    return true;
}

bool Robot::move()
{
    double speed = getSpeed();
    GameObject::move(Real(speed) * orientation_);
    if ( !(action_ & Robot::MOVING))
	{
        //To avoid continuous move toggling
        action_ += Robot::MOVING;
    }
    return true;
}

bool Robot::turnTurret (Ogre::Degree angle)
{
    //conversion for the quaternion's constructor (Degrees are more intuitive to use)
    Radian rotation(angle);
    Quaternion newDirection(angle, FORWARD_DEFAULT);
    turretOrientation_ = (newDirection * turretOrientation_).normalise();
    return true;
}

bool Robot::turnDirection (Ogre::Degree angle)
{
    //conversion for the quaternion's constructor (Degrees are more intuitive to use)
    Radian rotation(angle);
    Quaternion newDirection(angle, FORWARD_DEFAULT);
    orientation_ = (newDirection * orientation_).normalise();
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

Ogre::Vector3 Robot::getWheelOrientation() const
{
    return orientation_;
}

double Robot::getSpeed() const
{
    return stats_.getSpeed() + additionalStats_.getSpeed();
}

Ogre::Vector3 Robot::getTurretOrientation() const
{
    return turretOrientation_;
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
Robot::Robot()
    :stats_(),
	additionalStats_(),
	GameObject(),
	team_(NONE)
{
}

Robot::~Robot()
{
}
