#include <Ogre.h>
#include <string>
#include <vector>
#include "GameObject.h"
#include "Stats.h"
#include "Ability.h"
#include "Robot.h"


/*
 action_ modifying methods
*/
bool Robot::resetAction(){
    action_ = Robot::IDLE;
    return true;
}


bool Robot::fire(){
    //Something happens here to make the actual shooting
    if ( !(action_ & Robot::SHOOTING)){
        //To avoid continuous fire toggling
        action_ += Robot::SHOOTING;
    }
    return true;
}

bool Robot::move(){
    double speed = stats_.getSpeed() + additionalStats_.getSpeed();
    GameObject::Move(speed*orientation_);
    if ( !(action_ & Robot::MOVING)){
        //To avoid continuous move toggling
        action_ += Robot::MOVING;
    }
    return true;
}

bool turnTurret(Ogre::Degree angle){
    //conversion for the quaternion's constructor (Degrees are more intuitive to use)
    Ogre::Radian rotation(angle);
    Ogre::Quaternion newDirection(angle, FORWARD_DEFAULT);
    turretOrientation_ = (turretOrientation_*newDirection).normalise();
    return true;
}

bool turnDirection(Ogre::Degree angle){
    //conversion for the quaternion's constructor (Degrees are more intuitive to use)
    Ogre::Radian rotation(angle);
    Ogre::Quaternion newDirection(angle, FORWARD_DEFAULT);
    orientation_ = (orientation_*newDirection).normalise();
}


/*
Ability-based Methods
*/
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

/*
Basic Getters
*/

Ogre::Vector3 getWheelOrientation(){
    return orientation_;
}

double getSpeed(){
    return stats_.getSpeed() + additionalStats_.getSpeed();
}

Ogre::Vector3 getTurretOrientation(){
    return turretOrientation_;
}

Team getTeam(){
    return team_;
}

int getAction(){
    return action_;
}

bool isMoving(){
    return (action_ & MOVING);
}

bool isShooting(){
    return (action_ & SHOOTING);
}

bool isIDLE(){
    return (action_ == IDLE);
}


/*
Constructors & Destructors
*/
Robot::Robot()
    :stats_(),additionalStats_(),GameObject()
    {
#ifdef MAP
    cout << "Creation of Robot "<< name_ << endl;
#endif
    team_ = none;
    }

Robot::~Robot()
{
#ifdef MAP
    cout << "Destruction of Robot "<< name_ << endl;
#endif
}
#include "Robot.h"


Robot::Robot(void)
{
}

Robot::~Robot(void)
{
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

bool Robot::isIDLE() const
{
	return (action_ == IDLE);
}
