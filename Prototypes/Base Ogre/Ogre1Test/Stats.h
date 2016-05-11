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

	static const Stats STAT_ZERO;
	//Gauge energy = Gauge(), Gauge hp = Gauge(), double visionAngle = 60,
	//		int range = 300, int resistance = 0, double speed = 1.0

//------------------------------------------------------- Protected attributes
    Gauge		energy;	///< Gauge representing the energy of the robot ("mana")
    Gauge		hp;	///< Jauge representing the health points of the robot
    Gauge		visionAngle;	///< Gauge representing the angle of vision (and of aim) of the robot
    int			range;	///< Range of aim of the robot
    int			resistance;	///< Resistance to damage of the robot ("armor")
    float		speed;	///< Speed of the robot

public:

//------------------------------------------------- Operators overload
    Stats & operator+=(Stats const& otherStats);
    Stats & operator-=(Stats const& otherStats);
    friend std::ostream & operator<<(std::ostream & os, const Stats& stats);

//-------------------------------------------- Constructors - destructor
    /// Copy constructor
    /// @param otherStats Stats that we want to copy
    Stats ( const Stats & otherStats );

    /// Creates a set of statistics with the wished values
	/// @param energy wished energy
	/// @param hp wished health points
	/// @param visionAngle wished vision angle
	/// @param range wished range
	/// @param resistance wished resistance
	/// @param speed wished speed
    Stats (Gauge energy = Gauge(), Gauge hp = Gauge(), float visionAngle = 60,
			int range = 300, int resistance = 0, float speed = 1.0);


    ///Destroys an instance of Stats
    virtual ~Stats ();

private:
	void display(std::ostream &flux) const;

};

Stats operator+(Stats const& lhs, Stats const& rhs);
Stats operator-(Stats const& lhs, Stats const& rhs);


