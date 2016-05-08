#include "Ability.h"

using namespace std;

Ability::Ability(Robot* caster, string name, Gauge CD, Gauge casting, int damage, int range, double speed)
	: caster_(caster),
	CD_(CD),
	casting_(casting),
	damage_(damage),
	range_(range),
	speed_(speed),
	name_(name)
{
	CD_.setModifier(-1.f);//-1 for each turn so one second means 60 ticks
}

Ability::~Ability()
{
}

Gauge Ability::getCD() const
{
    return CD_;
}

Gauge Ability::getCasting() const
{
    return casting_;
}

int Ability::getDamage() const
{
    return damage_;
}

int Ability::getRange() const
{
    return range_;
}

double Ability::getSpeed() const
{
    return speed_;
}

string Ability::getName() const
{
    return name_;
}

Robot* Ability::getCaster() const
{
    return caster_;
}

void Ability::setCD(Gauge CD)
{
    CD_ = CD;
}

void Ability::setCasting(Gauge casting)
{
    casting_ = casting;
}

void Ability::setDamage(int damage)
{
    damage_ = damage;
}

void Ability::setRange(int range)
{
    range_ = range;
}

void Ability::setSpeed(double speed)
{
    speed_ = speed;
}

void Ability::setName(string name)
{
    name_ = name;
}

void Ability::setCaster(Robot* r)
{
    caster_ = r;
}

void Ability::update()
{
	CD_.update();
}
