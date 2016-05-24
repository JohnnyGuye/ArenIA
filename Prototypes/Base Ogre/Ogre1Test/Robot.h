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

class Robot: 
	public GameObject
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

	/// @brief Create a new robot
	/// @param position the initial position of the robot
	///	@param the name of the robot
	/// @param the team where he goes
    Robot(Ogre::Vector3 position = Ogre::Vector3::ZERO, std::string name = "", Team team = NONE);

    /** **/
    virtual ~Robot();

	virtual void reset();

    /// @brief  Reset the action state of the Robot to IDLE
    virtual bool Robot::resetAction();

    /// @brief Damages the Robot
    /// @param damage : the damages the robot took. Always higher than 0
    /// @return true if the damage killed the robot, false otherwise
    virtual bool takeDamage(float damage, GameObject* source);

	/// @brief verify intersection with an other hitbox
	/// @param hitbox : the other hitbox
	/// @return true if it collides
	virtual bool intersect(Hitbox* hitbox);

	/// @brief Update the robot using the lua file
	virtual void update();

	/// @brief applyChanges caused by the update on the robot
	virtual void applyUpdate(bool wallCollide = false);

    /// @brief  Called to make the Robot fire his turret
    /// @return True after a complete execution
    virtual bool fire();

    /// @brief  Called to make the Robot move
    virtual bool move();

	/// @brief	Returns the id of the robot
	virtual unsigned int getId();

	//--------------------------------------------------------------------DIRECTION
    /// @brief turn the turret by a certain amount of degrees
	/// @param angle this amount
    virtual bool turnTurret(const Ogre::Degree& angle);

    /// @brief Turn the robots direction (independant of the speed atm)
    virtual bool turnDirection(const Ogre::Degree& angle);

	/// @brief Set en orientation for the turret ranging from 0 to 360 degree from the x-axis
	virtual void setTurretOrientation(const Ogre::Degree& angle = Ogre::Degree(0));

	/// @brief The angle between the X-axis of the wheels, and the X-axis of the turret
	///	@return this angle in degrees 
	virtual Ogre::Degree getTurretOrientation() const;

	/// @brief a not really significant vector
    virtual Ogre::Vector3 getTurretOrientationVect() const;

	/// @brief get the position the robot will have after applying changes
	virtual Ogre::Vector3 getNextPosition() const;

	//----------------------------------------------------------------------ABILITY
    /// @brief Use the idxth Ability
    /// @param idxAbility : The index of the Ability to use
    /// @return True if the robot has an ability of that index
    bool useAbility(unsigned int idxAbility);

    /// @brief Returns the abilities known by a targeted Robot
    /// @param robot : the targeted robot
    /// @return The Competences possessed by the robot
    std::vector<Ability*> getKnownCompetences(Robot & robot);

    /// @brief Adds an ability
    /// @param anAbility : the Ability to add to the robot
    /// @return The index at which the ability the ability is inserted
    int addAbility(Ability * anAbility);

	/// @brief Remove the idxth ability
    /// @param idxAbility : the index of the ability to remove
    /// @return True if the ability was succesfully removed, False otherwise
    bool removeAbility(unsigned int idxAbility);

	/// @brief set the main ability of the robot, it is supposed to be direction dependant
	/// @param anAbility the ability to set
	void setTurretAbility(Ability * anAbility);

	/// @return the ability attach to the turret
	Ability* Robot::getTurretAbility() const;

	/// @return all the stats of the robot
	Stats getFullStats() const;

    /// @return the team of the robot
    virtual Team getTeam() const;

	/// @brief The way to know the current state of robot
	/// @return the state
	virtual State getState() const;

    /// @brief change this to set a new IA for the robot. 
	/// The loading is long, don't use it while playing
    void setIaFilename(std::string iaFilename);

    /// @brief Set the fightManager this robot is rellying on
    void setFightManager(FightManager* fightManager);

	/// @return the IA filename
	std::string getIaFilename() const;

	/// @return the fightManager associated to this robot
	FightManager* getFightManager() const;

	/// @return the list of abilities of this robot
	std::vector<Ability* > getAbilities() const;

    /// @return the list of the objects in the sight of this robot
    std::list<GameObject*> getSeenObjects(bool fetchRobots = true, bool fetchMissiles = true) const;

	//-------------------------------------------------------RENDERING
	virtual std::string getTurretMesh() const = 0;

	virtual Ogre::Real getScale() const = 0;
//attributes
protected:

    /** **/
    FightManager* fightManager_;
	/** **/
	Hitbox* hitbox_;

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

