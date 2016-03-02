#pragma once
/**
 * @file Stats.h
 * @author Samory Ka
 * @summary : This class represents a set of statistics representing a robot
 */


#define DEFAULT_RESISTANCE 0
#define DEFAULT_VISION_ANGLE 30
#define DEFAULT_RANGE 10
#define DEFAULT_SPEED 1

class Stats
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Operators overload
    Stats & operator = ( const Stats & otherStats );
    Stats & operator+=(Stats & otherStats);
    Stats & operator-=(Stats & otherStats);
    friend std::ostream & operator<<(std::ostream & os, Stats & stats)
    {
    	return os << "Stats: " << std::endl
    				  << "Energy: " << stats.getEnergy() << "/" << stats.getMaxEnergy() << std::endl
    				  << "HP: " << stats.getHp() << "/" << stats.getMaxHp() << std::endl
    				  << "Vision angle: " << stats.getVisionAngle() << "/" << stats.getMaxVisionAngle() << std::endl
    				  << "Range: " << stats.getRange() << std::endl
    				  << "Speed: " << stats.getSpeed() << std::endl
    				  << "Resistance: " << stats.getResistance() << std::endl;
    }

    /**
     * @TODO
     */
    friend std::istream & operator>>(std::istream & os, Stats & stats);





//-------------------------------------------- Constructors - destructor
    /**
     * Copy constructor
     * @param otherStats Stats that we want to copy
     */
    Stats ( const Stats & otherStats );


    /**
     *
     * Default constructor
     * Creates a set of statistics with default values (DEFAULT_*)
     */
    Stats ();


    /**
	* Primary constructor
	* Creates a set of statistics with the wished values
	* @param energy wished energy
	* @param hp wished health points
	* @param visionAngle wished vision angle
	* @param range wished range
	* @param resistance wished resistance
	* @param speed wished speed
	*/
    Stats ( Gauge energy, Gauge hp, Gauge visionAngle, int range, int resistance, int speed);


    /**
	 * Destructor
	 * Destroys an instance of Stats
	 */
    virtual ~Stats ();

//------------------------------------------------- Public methods


//--------------------------------------GETTERS

    /**
	* Energy getter
	* Returns the current energy of the robot
	* @return energy_.current statistic
	*/
    double getEnergy();


    /**
	* Maximum energy getter
	* Returns the maximum energy of the robot
	* @return energy_.max
	*/
	int getMaxEnergy();

	 /**
	* Energy modifier getter
	* Returns the current energy modifier of the robot
	* @return energy_.modifier statistic
	*/
	double getEnergyModifier();


    /**
	* Health points getter
	* Returns the current health points of the robot
	* @return hp_.current statistic
	*/
	double getHp();


	/**
	* Maximum health points getter
	* Returns the maximum health points of the robot
	* @return hp_.max
	*/
	int getMaxHp();


	/**
	* Health points modifier getter
	* Returns the current health points modifier of the robot
	* @return hp_.modifier statistic
	*/
	double getHpModifier();


	/**
	* Vision angle getter
	* Returns the current vision angle of the robot
	* @return visionAngle_.current statistic
	*/
	double getVisionAngle();


	/**
	* Maximum vision angle getter
	* Returns the maximum vision angle of the robot
	* @return visionAngle_.max
	*/
	int getMaxVisionAngle();

	/**
	* Vision angle modifier getter
	* Returns the current vision angle modifier of the robot
	* @return visionAngle_.modifier statistic
	*/
	double getVisionAngleModifier();

	/**
	* Speed getter
	* Returns the speed of the robot
	* @return speed_ statistic
	*/
    double getSpeed();

    /**
	* Resistance getter
	* Returns the resistance of the robot
	* @return resistance_ statistic
	*/
    int getResistance();

    /**
	* Range getter
	* Returns the range of the robot
	* @return range_ statistic
	*/
    int getRange();



//--------------------------------------SETTERS

    /**
	* Energy setter
	* Sets the current energy to value
	* @param value The value that you want energy_.current to become
	*/
    void setEnergy( double value );


    /**
	* Energy modifier setter
	* Sets the energy modifier to value
	* @param value The value that you want energy_.modifier to become
	*/
    void setEnergyModifier ( double value );


    /**
	* Health points setter
	* Sets the current health points to value
	* @param value The value that you want hp_.current to become
	*/
    void setHp( double value);


    /**
	* Health points modifier setter
	* Sets the health points modifier to value
	* @param value The value that you want hp_.modifier to become
	*/
	void setHpModifier ( double value );


    /**
	* Vision angle setter
	* Sets the current vision angle to value
	* @param value The value that you want visionAngle_.current to become
	*/
    void setVisionAngle( double value );


    /**
	* Vision angle modifier setter
	* Sets the vision angle modifier to value
	* @param value The value that you want visionAngle_.modifier to become
	*/
	void setVisionAngleModifier ( double value );


    /**
   	* Speed setter
   	* Sets speed_ to value
   	* @param value The value that you want speed_ to become
   	*/
    void setSpeed( double value );

    /**
	* Resistance setter
	* Sets resistance_ to value
	* @param value The value that you want resistance_ to become
	*/
    void setResistance( int value);

    /**
   	* Range setter
   	* Sets range_ to value
   	* @param value The value that you want range_ to become
   	*/
    void setRange( int value );



//----------------------------------------------------------------- PROTECTED
protected:
//------------------------------------------------------- Protected attributes
    Gauge energy_;	///< Gauge representing the energy of the robot ("mana")
    Gauge hp_;	///< Jauge representing the health points of the robot
    Gauge visionAngle_;	///< Gauge representing the angle of vision (and of aim) of the robot
    int range_;	///< Range of aim of the robot
    int resistance_;	///< Resistance to damage of the robot ("armor")
    double speed_;	///< Speed of the robot


};


