#pragma once

/*
* ARENIA project
* Robot.h
*
* @author Simon Belletier
* @summary :  Header file of the Robot Class, a Robot is the main fighting entity.
*/

#include "GameEvent.h"
#include "RobotKillEvent.h"
#include "GameObject.h"
#include "Stats.h"
#include "Ability.h"
#include "Terrain.h"
#include "LuaHandler.h"
#include "HitboxSphere.h"

class FightManager;

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
		LAVE_LINGE,
		TONDEUSE
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

    /** @brief Damages the Robot
        @param damage : the damages the robot took. Always higher than 0
        @return ROBOT_KILL if the damage killed the robot, STANDARD_EVENT otherwise**/
    virtual bool takeDamage(float damage, GameObject* source);

	/** @brief Update the robot using the lua file **/
	virtual void update();

	/** @brief applyChanges caused by the update on the robot **/
	virtual void applyUpdate(bool wallCollide = false);

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

	virtual Ogre::Vector3 getNextPosition() const;

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
    int addAbility(Ability * anAbility);

    /** @brief Remove the idxth ability
        @param idxAbility : the index of the ability to remove
        @return True if the ability was succesfully removed, False otherwise
    **/

	void setTurretAbility(Ability * anAbility);

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
    void setIaFilename(std::string iaFilename);

    /** **/
    void setFightManager(FightManager* fightManager);

	/** **/
	std::string getIaFilename() const;

	/** **/
	FightManager* getFightManager() const;

	/** **/
	std::vector<Ability* > getAbilities() const;

    /** **/
    std::list<GameObject*> getSeenObjects(bool fetchRobots = true, bool fetchMissiles = true) const;//pas const dans le doute, mais devrait le devenir

	/** **/
	Ability* Robot::getTurretAbility() const;

//attributes
protected:

    /** **/
    FightManager* fightManager_;

    /**The robot Id, generated for now by a static count**/
    static int robot_count;
	static const std::string IA_PATH;

    int id_;
    /** The teams to which the Robot Belongs **/
    Team team_;

    /** The base stats of the Robot**/
    Stats stats_;

    /** modifier for the base stats **/
    Stats additionalStats_;

    /** The Robot's abilities **/
    std::vector<Ability*> abilities_;

    /** The turret -> the Robot's default ability **/
    Ability* turret_;

    /** Current actions done by the robot**/
    State action_;

    /** The IA's filename **/
    std::string		iaFilename_;
	LuaHandler*		luaCode_;

    /**Turret Orientation**/
    Ogre::Vector3	turretOrientation_;
	Ogre::Degree	turretAngle_;

	Ogre::Vector3	nextPosition_;
	/**The last thing that damaged the robot**/
	GameObject* lastDamageSource_;
};

