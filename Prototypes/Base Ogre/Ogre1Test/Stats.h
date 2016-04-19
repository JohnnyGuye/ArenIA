#pragma once
/**
 * @file Stats.h
 * @author Samory Ka
 * @summary : This class represents a set of statistics representing a robot
 */

#include <string>
#include <iostream>
#include "Gauge.h"

class Stats
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Operators overload
    Stats & operator+=(Stats & otherStats);
    Stats & operator-=(Stats & otherStats);
    friend std::ostream & operator<<(std::ostream & os, const Stats& stats);

    /**
     * @TODO
     */
    friend std::istream & operator>>(std::istream & os, Stats& stats);

//-------------------------------------------- Constructors - destructor
    /**
     * Copy constructor
     * @param otherStats Stats that we want to copy
     */
    Stats ( const Stats & otherStats );

    /**
	* Creates a set of statistics with the wished values
	* @param energy wished energy
	* @param hp wished health points
	* @param visionAngle wished vision angle
	* @param range wished range
	* @param resistance wished resistance
	* @param speed wished speed
	*/
    Stats (Gauge energy = Gauge(), Gauge hp = Gauge(), double visionAngle = 60,
			int range = 300, int resistance = 0, double speed = 1.0);


    /**
	 * Destructor
	 * Destroys an instance of Stats
	 */
    virtual ~Stats ();

//------------------------------------------------- Public methods




public:

	static const Stats STAT_ZERO;
	//Gauge energy = Gauge(), Gauge hp = Gauge(), double visionAngle = 60,
	//		int range = 300, int resistance = 0, double speed = 1.0

public:
//------------------------------------------------------- Protected attributes
    Gauge energy_;	///< Gauge representing the energy of the robot ("mana")
    Gauge hp_;	///< Jauge representing the health points of the robot
    Gauge visionAngle_;	///< Gauge representing the angle of vision (and of aim) of the robot
    int range_;	///< Range of aim of the robot
    int resistance_;	///< Resistance to damage of the robot ("armor")
    double speed_;	///< Speed of the robot


};


