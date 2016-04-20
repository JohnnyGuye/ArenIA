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
const Stats Stats::STAT_ZERO(Gauge(), Gauge(), 60.f, 300, 0, 1.0f);

//------------------------------------------------- Operators overload
Stats & Stats::operator+=(Stats & otherStats)
{
	energy+=otherStats.energy;
	energy.setModifier(energy.getModifier() + otherStats.energy.getModifier());

	hp+=otherStats.hp;
	hp.setModifier(hp.getModifier() + otherStats.hp.getModifier());

	visionAngle.setCurrent(visionAngle.getCurrent() + otherStats.visionAngle.getCurrent());
	visionAngle.setModifier(visionAngle.getModifier() + otherStats.visionAngle.getModifier());

	range+=otherStats.range;
	speed+=otherStats.speed;
	resistance+=otherStats.resistance;

	return *this;

}


Stats & Stats::operator-=(Stats & otherStats)
{
	energy -= otherStats.energy;
	energy.setModifier(energy.getModifier() - otherStats.energy.getModifier());

	hp -= otherStats.hp;
	hp.setModifier(hp.getModifier() - otherStats.hp.getModifier());

	visionAngle.setCurrent(visionAngle.getCurrent() - otherStats.visionAngle.getCurrent());
	visionAngle.setModifier(visionAngle.getModifier() - otherStats.visionAngle.getModifier());

	range -= otherStats.range;
	speed -= otherStats.speed;
	resistance -= otherStats.resistance;

	return *this;

}

//-------------------------------------------- Constructors - destructor
Stats::Stats ( const Stats & otherStats )
	:
	energy(otherStats.energy),
	hp(otherStats.hp),
	visionAngle(otherStats.visionAngle),
	range(otherStats.range),
	resistance(otherStats.resistance),
	speed(otherStats.speed)
	{
	}


Stats::Stats ( Gauge energy, Gauge hp, float visionAngle, int range, int resistance, float speed)
	: energy(energy),
	hp(hp),
	visionAngle(360,0,visionAngle),
	resistance(resistance),
	speed(speed)
{
}

Stats::~Stats ()
{
}

void Stats::display(ostream &flux) const
{
	flux << "Stats: " << endl
		<< "Energy: " << energy.getCurrent() << "/" << energy.getMax() << endl
		<< "HP: " << hp.getCurrent() << "/" << hp.getMax() << endl
		<< "Vision angle: " << visionAngle.getCurrent() << "/" << visionAngle.getMax() << endl
		<< "Range: " << range << endl
		<< "Speed: " << speed << endl
		<< "Resistance: " << resistance << endl;
}

ostream& operator<<(ostream& os, const Stats& stats)
{
	stats.display(os);
	return os;
}
