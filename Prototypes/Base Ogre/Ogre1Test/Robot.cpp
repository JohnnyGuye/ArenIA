#include "Robot.h"

#include <Ogre.h>
#include <string>
#include <vector>

#include "GameObject.h"
#include "Stats.h"
#include "Ability.h"

using namespace Ogre;
using namespace std;

/*
 action_ modifying methods
*/


Robot::Robot(Vector3 position, string name)
	: GameObject(position, name),
    team_(NONE),
	stats_(),
	additionalStats_(),
	action_(IDLE),
	iaFilename_("EMPTY")
{
	setTurretOrientation();
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
    action_ = (State)(action_ | SHOOTING);
    return true;
}

bool Robot::move()
{
    double speed = getSpeed();
    GameObject::move(Real(speed) * orientation_);
    action_ = (State)(action_ | MOVING);
    return true;
}

bool Robot::turnTurret (const Degree& angle)
{
	if(isSnared())	return false;
	setTurretOrientation(angle);
    return true;
}

bool Robot::turnDirection (const Degree& angle)
{
	if (isSnared())	return false;
    setOrientation(angle);
	return true;
}

void Robot::setTurretOrientation(const Degree& angle)
{
	turretAngle_ = angle;
	Real sin = Math::Sin(angle.valueRadians());
	Real cos = Math::Cos(angle.valueRadians());

	turretOrientation_ = Ogre::Vector3(sin, 0, cos);
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

Degree Robot::getTurretAngle() const
{
	return Degree(turretOrientation_.angleBetween(orientation_));
}

Vector3 Robot::getTurretOrientation() const
{
    return turretOrientation_;
}

double Robot::getSpeed() const
{
    return stats_.getSpeed() + additionalStats_.getSpeed();
}

Robot::Team Robot::getTeam() const
{
	return team_;
}

Robot::State Robot::getState() const
{
	return action_;
}