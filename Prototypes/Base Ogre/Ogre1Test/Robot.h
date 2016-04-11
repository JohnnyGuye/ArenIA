#pragma once

/*
* ARENIA project
* Robot.h
*
* @author Simon Belletier
* @summary :  Header file of the Robot Class, a Robot is the main fighting entity.
*/

#include <Ogre.h>
#include <string>
#include <vector>
#include <string>

#include "GameObject.h"
#include "Stats.h"
#include "Ability.h"
#include "Terrain.h"

//for the rotations
#define FORWARD_DEFAULT Ogre::Vector3::NEGATIVE_UNIT_Z

class Robot: public GameObject
{
//constants
public:
    /** Used  **/
    enum State {
		IDLE = 0,
		TURNING_WHEELS = 1,
        MOVING = 2,
        TURNING_TURRET = 4,
        SHOOTING = 8
	};

	enum Team {
		NONE = 0,
		BLACK = 1,
		WHITE = 2,
		BLUE = 4,
		PURPLE = 8,
		RED = 16,
		ORANGE = 32,
		YELLOW = 64,
		GREEN = 128
    };

	enum Type {
		LAVE_LINGE
	};

//public methods
public:

	/** @brief Create a new robot
	*	@param position the initial position of the robot
	*	@param the name of the robot **/
    Robot(Ogre::Vector3 position = Ogre::Vector3::ZERO, std::string name = "", Team team = NONE);

    /** **/
    virtual ~Robot();

    /** @brief  Reset the action state of the Robot to IDLE**/
    virtual bool Robot::resetAction();

	virtual void update();

    /** @brief  Called to make the Robot fire his turret
        @return True after a complete execution**/
    virtual bool fire();

    /** @brief  Called to make the Robot move**/
    virtual bool move();

    /** **/
    virtual bool turnTurret(const Ogre::Degree& angle);

    /** @brief Turn the robots direction (independant of the speed for nom)**/
    virtual bool turnDirection(const Ogre::Degree& angle);

	virtual void setTurretOrientation(const Ogre::Degree& angle = Ogre::Degree(0));

    /** @brief Use the idxth Ability
        @param idxAbility : The index of the Ability to use
        @return True if the robot has an ability of that index
    **/
    bool useAbility(unsigned int idxAbility);

    /** @brief Returns the abilities known by a targeted Robot
        @param robot : the targeted robot
        @return The Competences possessed by the robot
    **/
    std::vector<Ability*> getKnownCompetences(Robot & robot);

    /** @brief Adds an ability
        @param anAbility : the Ability to add to the robot
        @return The index at which the ability the ability is inserted
    **/
    int addAbility(Ability & anAbility);

    /** @brief Remove the idxth ability
        @param idxAbility : the index of the ability to remove
        @return True if the ability was succesfully removed, False otherwise
    **/
    bool removeAbility(unsigned int idxAbility);


	/** @brief a not really significant vector **/
    virtual Ogre::Vector3 getTurretOrientationVect() const;

	/** @brief The angle between the X-axis of the wheels, and the X-axis of the turret
	*	@return this angle in degrees **/
	virtual Ogre::Degree getTurretOrientation() const;

    /** **/
    virtual double getSpeed() const;

    /** **/
    virtual Team getTeam() const;

	/** @brief The way to know the current state of robot
	*	@return the state **/
	virtual State getState() const;

	/** **/
	std::vector<Ability* > getAbilities() const;

//attributes
protected:

    /** The teams to which the Robot Belongs **/
    Team team_;

    /** The base stats of the Robot**/
    Stats stats_;

    /** modifier for the base stats **/
    Stats additionalStats_;

    /** The Robot's abilities **/
    std::vector<Ability*> abilities_;

    /** Current actions done by the robot**/
    State action_;

    /** The IA's filename **/
    std::string iaFilename_;

    /**Turret Orientation**/
    Ogre::Vector3 turretOrientation_;
	Ogre::Degree turretAngle_;

};

