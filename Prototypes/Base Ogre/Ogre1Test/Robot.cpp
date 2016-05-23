#include "Robot.h"
#include "RobotLuaBinding.h"
#include "AbilityMissile.h"
#include "HitboxSphere.h"

using namespace Ogre;
using namespace std;

const string Robot::IA_PATH ("../IAs/");
/*
 action_ modifying methods
*/
//-------------------------------------------------CONSTANTES
int Robot::robot_count = 1;

//----------------------------------------------------METHODS
Robot::Robot(Vector3 position, string name, Robot::Team team)
	: GameObject(position, name),
	nextPosition_(position),
    team_(team),
	stats_(Gauge(), Gauge(), 60, 500, 0, 4.0),
	additionalStats_(Gauge(0), Gauge(0), 0, 0, 0, 0),
	action_(IDLE),
	hitbox_(new HitboxSphere(&position_, 50, Ogre::Vector3(0,50,0))),
	id_(robot_count++)
{
	lastDamageSource_ = nullptr;
	setTurretOrientation();
	luaCode_ = new LuaHandler();
	setIaFilename("default.lua");
}

Robot::~Robot()
{
	delete luaCode_;
	if(hitbox_) delete hitbox_;
}

void Robot::reset()
{
	stats_.hp.fill();
	stats_.energy.fill();
	dead_ = false;
	setIaFilename(iaFilename_);
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
	turret_->update();
	for(unsigned int i=0; i < abilities_.size(); i++)
	{
		abilities_[i]->update();
	}
	resetAction();
	RobotLuaBinding::setRobot(this);
	luaCode_->Execute();
}

void Robot::applyUpdate(bool wallCollide)
{
	if(!wallCollide)	position_ = nextPosition_;
}

bool Robot::fire()
{
	turret_->cast();
    action_ = (State)(action_ | SHOOTING);
    return true;
}

bool Robot::move()
{
	if( (action_ & MOVING) == MOVING)	return false;
	if( isSnared() )		return false;
    nextPosition_ = position_ + (Real(getFullStats().speed) * orientation_);
    action_ = (State)(action_ | MOVING);
    return true;
}

unsigned int Robot::getId()
{
	return id_;
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
        abilities_[idxAbility]->cast();
        return true;
    }
    return false;
}

std::vector<Ability*> Robot::getKnownCompetences(Robot & robot){
    return robot.abilities_;
}

int Robot::addAbility(Ability * anAbility){
    abilities_.push_back(anAbility);
    return abilities_.size() - 1;//returns the index of the Ability inserted
}

void Robot::setTurretAbility(Ability *anAbility){
	turret_ = anAbility;
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

Stats Robot::getFullStats() const
{
	return stats_ + additionalStats_;
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

std::string Robot::getIaFilename() const
{
    return iaFilename_;
}

FightManager* Robot::getFightManager() const
{
    return fightManager_;
}

/* Setters */

void Robot::setIaFilename(std::string iaFilename)
{
    iaFilename_ = iaFilename;
    std::stringstream ss;
	ss << IA_PATH << iaFilename_;
	luaCode_->LoadFile(ss.str().c_str());
}

void Robot::setFightManager( FightManager* fightManager )
{
    fightManager_ = fightManager;
}


/* Stats altering method */
bool Robot::takeDamage(float damage, GameObject* source)
//Algorithm : the damage is first taken in the additional health gauge
//The Robot dies if the base gauge is depleted
{
    lastDamageSource_ = source;
	if(isInvincible())	return false;
    //Step 1 : Apply the damage
    if( additionalStats_.hp.getFilledAbsolute() >= damage )
    {
        additionalStats_.hp.setCurrent( additionalStats_.hp.getCurrent() - damage );
    }
    else if ( additionalStats_.hp.getFilledAbsolute() > 0 )
    {
        float damageBaseGauge = damage - additionalStats_.hp.getFilledAbsolute();
        additionalStats_.hp.setCurrent( additionalStats_.hp.getCurrent() - damage );
        stats_.hp.setCurrent( stats_.hp.getCurrent() - damageBaseGauge );
    }
    else
    {
        stats_.hp.setCurrent( stats_.hp.getCurrent() - damage );
    }
    //Step 2 : Check for the robot death
    if ( stats_.hp.getFilledAbsolute() == 0 )
    {
        return true;
    }
    else//could end up as a ROBOT_HIT event
    {
        return false;
    }
}

bool Robot::intersect(Hitbox* hitbox)
{
	return (hitbox_->intersect(hitbox));
}


std::list<GameObject*> Robot::getSeenObjects(bool fetchRobots, bool fetchMissiles) const
//TODO someday, replace the input by some flags (just not urgent)
{
	std::list<GameObject*> seenObjects;
	if( fetchRobots )
	{
		std::list<Robot*> Robots = fightManager_->getRobots();
		for(std::list<Robot*>::iterator it = Robots.begin() ; it != Robots.end() ; it++)
		{
			Ogre::Vector3 dist = (*it)->getPosition() - position_ ;
			int range = (stats_.range + additionalStats_.range);
			if( dist.squaredLength() <= range*range )
			{
				//separation for the readability of the conditions
				Ogre::Real visionAngle( (stats_.visionAngle.getCurrent() + additionalStats_.visionAngle.getCurrent())/2 );
				if( dist.angleBetween( getTurretOrientationVect() ).valueDegrees() <= visionAngle  )
				{
					seenObjects.push_back( (*it) );
				}
			}
		}
	}

	if( fetchMissiles )
	{
		std::list<Missile*> Missiles = fightManager_->getMissiles();
		for(std::list<Missile*>::iterator it = Missiles.begin() ; it != Missiles.end() ; it++)
		{
			Ogre::Vector3 dist = (*it)->getPosition() - position_ ;
			int range = (stats_.range + additionalStats_.range);
			if( dist.squaredLength() <= range*range )
			{
				//separation for the readability of the conditions
				Ogre::Real visionAngle( (stats_.visionAngle.getCurrent() + additionalStats_.visionAngle.getCurrent())/2 );
				if( dist.angleBetween( getTurretOrientationVect() ).valueDegrees() <= visionAngle  )
				{
					seenObjects.push_back( (*it) );
				}
			}
		}

	}

	return seenObjects;
}