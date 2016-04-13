#include "Robot.h"

using namespace Ogre;
using namespace std;

/*
 action_ modifying methods
*/


Robot::Robot(Vector3 position, string name, Robot::Team team)
	: GameObject(position, name),
	nextPosition_(position),
    team_(team),
	stats_(Gauge(), Gauge(), 60, 500, 0, 4.0),
	additionalStats_(Gauge(0), Gauge(0), 0, 0, 0, 0),
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

Vector3 Robot::getNextPosition() const
{
	return nextPosition_;
}

void Robot::update()
{
	resetAction();
	turnDirection(Degree(rand() / (double)RAND_MAX * 20 - 10));
	move();
}

void Robot::applyUpdate(bool wallCollide)
{
	if(!wallCollide)	position_ = nextPosition_;
}

bool Robot::fire()
{
    turret_->Cast();
    action_ = (State)(action_ | SHOOTING);
    return true;
}

bool Robot::move()
{
	if( (action_ & MOVING) == MOVING)	return false;
	if( isSnared() )		return false;
    double speed = getSpeed();
    nextPosition_ = position_ + (Real(speed) * orientation_);
    action_ = (State)(action_ | MOVING);
    return true;
}

bool Robot::turnTurret (const Degree& angle)
{
	if(isSnared())	return false;
	setTurretOrientation(angle_ + angle);
    return true;
}

bool Robot::turnDirection (const Degree& angle)
{
	if (isSnared())	return false;
    setOrientation(angle_ + angle);
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

bool Robot::useAbility(unsigned int idxAbility){
    if(idxAbility >= 0 && idxAbility < abilities_.size() )
    {
        abilities_[idxAbility]->Cast();
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<Ability*> Robot::getKnownCompetences(Robot & robot){
    return robot.abilities_;
}

int Robot::addAbility(Ability & anAbility){
    abilities_.push_back(&anAbility);
    return abilities_.size() - 1;//returns the index of the Ability inserted
}

void Robot::setTurretAbility(Ability & anAbility){
	turret_ = &anAbility;
}

bool Robot::removeAbility(unsigned int idxAbility){
    if(idxAbility < abilities_.size() )
    {
		abilities_.erase(abilities_.begin() + idxAbility );
        return true;
    }
    else
    {
        return false;
    }
}

/*
Basic Getters
*/

Degree Robot::getTurretOrientation() const
{
	return Degree(turretOrientation_.angleBetween(orientation_));
}

Vector3 Robot::getTurretOrientationVect() const
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

std::vector<Ability*> Robot::getAbilities() const
{
	return abilities_;
}

Ability* Robot::getTurretAbility() const
{
	return turret_;
}