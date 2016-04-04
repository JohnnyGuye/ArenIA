/**
 * @file Ability.cpp
 * @author Alp Yğcesoy
 */
 
 using namespace std;
#include <iostream>
#include <string>
#include "Ability.h"
#include "Gauge.h"

Ability::Ability()
{
     damage_ = DEFAULT_DAMAGE;
     range_ = DEFAULT_RANGE;
     speed_ = DEFAULT_SPEED;
}

Ability::Ability(Gauge CD, Gauge casting, int damage, int range, double speed, string name)
{
    CD_ = CD;
    casting_ = casting;
    damage_ = damage;
    range_ = range;
    speed_ = speed;
    name_ = name;
}

Gauge Ability::getCD()
{
    return CD_;
}

Gauge Ability::getcasting()
{
    return casting_;
}

int Ability::getdamage()
{
    return damage_;
}

int Ability::getrange()
{
    return range;
}

double Ability::getspeed()
{
    return speed_;
}

string Ability::getname()
{
    return name_;
}

void Ability::setCD(Gauge CD)
{
    CD_ = CD;
}

void Ability::setcasting(Gauge casting)
{
    casting_ = casting;
}

void Ability::setdamage(int damage)
{
    damage_ = damage;
}

void Ability::setrange(int range)
{
    range_ = range;
}

void Ability::setspeed(double speed)
{
    speed_ = speed;
}

void Ability::setname(string name)
{
    name_ = name;
}

void Ability::Do()
{
    
}