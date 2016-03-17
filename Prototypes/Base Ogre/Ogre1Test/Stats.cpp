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
Stats::Stats ( const Stats & otherStats )
	: 
	energy_(otherStats.energy_),
	hp_(otherStats.hp_),
	visionAngle_(otherStats.visionAngle_),
	range_(otherStats.range_),
	resistance_(otherStats.resistance_),
	speed_(otherStats.speed_)
	{
	}


Stats::Stats ( Gauge energy, Gauge hp, double visionAngle, int range, int resistance, double speed)
	: energy_(energy),
	hp_(hp),
	visionAngle_(360,0,visionAngle),
	resistance_(resistance),
	speed_(speed)
{
}

Stats::~Stats ()
{
}

//------------------------------------------------- Public methods

//--------------------------------------GETTERS
double Stats::getEnergy() const
{
	return energy_.getCurrent();
}

double Stats::getHp() const
{
	return hp_.getCurrent();
}

double Stats::getVisionAngle() const
{
	return visionAngle_.getCurrent();
}

int Stats::getMaxEnergy() const
{
	return energy_.getMax();
}

int Stats::getMaxHp() const
{
	return hp_.getMax();
}

int Stats::getMaxVisionAngle() const
{
	return visionAngle_.getMax();
}

double Stats::getEnergyModifier() const
{
	return energy_.getModifier();
}

double Stats::getHpModifier() const
{
	return hp_.getModifier();
}

double Stats::getVisionAngleModifier() const
{
	return visionAngle_.getModifier();
}

double Stats::getSpeed() const
{
	return speed_;
}

int Stats::getResistance() const
{
	return resistance_;
}

int Stats::getRange() const
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

void Stats::display(ostream &flux) const
{
	flux << "Stats: " << endl
		<< "Energy: " << getEnergy() << "/" << getMaxEnergy() << endl
		<< "HP: " << getHp() << "/" << getMaxHp() << endl
		<< "Vision angle: " << getMaxEnergy() << "/" << getMaxVisionAngle() << endl
		<< "Range: " << getRange() << endl
		<< "Speed: " << getSpeed() << endl
		<< "Resistance: " << getResistance() << endl;
}
ostream& operator<<(ostream& os, const Stats& stats)
{
	stats.display(os);
	return os;
}