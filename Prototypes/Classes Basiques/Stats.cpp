/**
* @file Stats.cpp
* @author Samory Ka
* @summary : This class represents a set of statistics representing a robot
*/

#include <iostream>

#include "Gauge.h"
#include "Stats.h"
using namespace std;

//----------------------------------------------------------------- PUBLIC


//------------------------------------------------- Operators overload
Stats & Stats::operator = ( const Stats & otherStats )
{
	energy_ = otherStats.energy_;
	hp_ = otherStats.hp_;
	visionAngle_ = otherStats.visionAngle_;
	range_ = otherStats.range_;
	resistance_ = otherStats.resistance_;
	speed_ = otherStats.speed_;

	return *this;
}


Stats & Stats::operator+=(Stats & otherStats)
{

	double newEnergy = this->getEnergy() + otherStats.getEnergy();
	this->setEnergy( newEnergy );

	double newEnergyModifier = this->getEnergyModifier() + otherStats.getEnergyModifier();
	this->setEnergyModifier( newEnergyModifier );


	double newHp = this->getHp() + otherStats.getHp();
	this->setHp( newHp);

	double newHpModifier = this->getHpModifier() + otherStats.getHpModifier();
	this->setEnergyModifier( newHpModifier );


	double newVisionAngle = this->getVisionAngle() + otherStats.getVisionAngle();
	this->setVisionAngle( newVisionAngle );

	double newVisionAngleModifier = this->getVisionAngleModifier() + otherStats.getVisionAngleModifier();
	this->setEnergyModifier( newVisionAngleModifier );


	this->setRange( this->getRange() + otherStats.getRange() );

	this->setResistance( this->getResistance() + otherStats.getResistance() );

	this->setSpeed( this->getSpeed() + otherStats.getSpeed() );

	return *this;

}


Stats & Stats::operator-=(Stats & otherStats)
{


	double newEnergy = this->getEnergy() - otherStats.getEnergy();
	this->setEnergy( newEnergy );

	double newEnergyModifier = this->getEnergyModifier() - otherStats.getEnergyModifier();
	this->setEnergyModifier( newEnergyModifier );


	double newHp = this->getHp() - otherStats.getHp();
	this->setHp( newHp);

	double newHpModifier = this->getHpModifier() - otherStats.getHpModifier();
	this->setEnergyModifier( newHpModifier );


	double newVisionAngle = this->getVisionAngle() - otherStats.getVisionAngle();
	this->setVisionAngle( newVisionAngle );

	double newVisionAngleModifier = this->getVisionAngleModifier() - otherStats.getVisionAngleModifier();
	this->setEnergyModifier( newVisionAngleModifier );


	this->setRange( this->getRange() - otherStats.getRange() );

	this->setResistance( this->getResistance() - otherStats.getResistance() );

	this->setSpeed( this->getSpeed() - otherStats.getSpeed() );

	return *this;

}



//-------------------------------------------- Constructors - destructor
/**
 * Copy constructor
 * @param otherStats Stats that we want to copy
 */
Stats::Stats ( const Stats & otherStats )
{
	energy_ = otherStats.energy_;
	hp_ = otherStats.hp_;
	visionAngle_ = otherStats.visionAngle_;
	range_ = otherStats.range_;
	resistance_ = otherStats.resistance_;
	speed_ = otherStats.speed_;
}


/**
 *
 * Default constructor
 * Creates a set of statistics with default values (DEFAULT_*)
 */
Stats::Stats ()
{
	Gauge defaultGauge;
	energy_ = defaultGauge;
	hp_ = defaultGauge;
	visionAngle_ = Gauge(360, 0, DEFAULT_VISION_ANGLE, 1);
	range_ = DEFAULT_RANGE;
	resistance_ = DEFAULT_RESISTANCE;
	speed_ = DEFAULT_SPEED;
}


Stats::Stats ( Gauge energy, Gauge hp, Gauge visionAngle, int range, int resistance, int speed)
{
	energy_ = energy;
	hp_ = hp;
	visionAngle_ = visionAngle;
	range_ = range;
	resistance_ = resistance;
	speed_ = speed;
}


/**
 * Destructor
 * Destroys an instance of Stats
 */
Stats::~Stats ()
{

}

//------------------------------------------------- Public methods

//--------------------------------------GETTERS
double Stats::getEnergy()
{
	return energy_.getCurrent();
}


double Stats::getHp()
{
	return hp_.getCurrent();
}



double Stats::getVisionAngle()
{
	return visionAngle_.getCurrent();
}



int Stats::getMaxEnergy()
{
	return energy_.getMax();
}


int Stats::getMaxHp()
{
	return hp_.getMax();
}


int Stats::getMaxVisionAngle()
{
	return visionAngle_.getMax();
}


double Stats::getEnergyModifier()
{
	return energy_.getModifier();
}


double Stats::getHpModifier()
{
	return hp_.getModifier();
}


double Stats::getVisionAngleModifier()
{
	return visionAngle_.getModifier();
}


double Stats::getSpeed()
{
	return speed_;
}


int Stats::getResistance()
{
	return resistance_;
}



int Stats::getRange()
{
	return range_;
}



//--------------------------------------SETTERS

void Stats::setEnergy( double value )
{
	energy_.setCurrent( value );
}


void Stats::setEnergyModifier ( double value )
{
	energy_.setModifier( value );
}


void Stats::setHp( double value)
{
	hp_.setCurrent( value );
}


void Stats::setHpModifier ( double value )
{
	hp_.setModifier( value );
}


void Stats::setVisionAngle( double value )
{
	visionAngle_.setCurrent( value );
}


void Stats::setVisionAngleModifier ( double value )
{
	visionAngle_.setModifier( value );
}


void Stats::setSpeed( double value )
{
	speed_ = value;
}


void Stats::setResistance( int value)
{
	resistance_ = value;
}


void Stats::setRange( int value )
{
	range_ = value;
}




