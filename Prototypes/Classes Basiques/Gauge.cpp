/**
 * @file Gauge.cpp
 * @author Samory Ka
 */

using namespace std;
#include <iostream>

#include "Gauge.h"

//------------------------------------------------- Operators overload
Gauge & Gauge::operator = ( const Gauge & unGauge )
{
	this->max_ = unGauge.max_;
	this->min_ = unGauge.min_;
	this->current_ = unGauge.current_;
	this->modifier_ = unGauge.modifier_;

	return *this;
}



//-------------------------------------------- Constructors - destructor
Gauge::Gauge ( const Gauge & unGauge )
{
	max_ = unGauge.max_;
	min_ = unGauge.min_;
	current_ = unGauge.current_;
	modifier_ = unGauge.modifier_;
}


Gauge::Gauge ()
{
	max_ = DEFAULT_MAX;
	min_ = DEFAULT_MIN;
	current_ = DEFAULT_MAX;
	modifier_ = DEFAULT_MODIFIER;
}

Gauge::Gauge ( int max, int min, double modifier )
{
	max_ = max;
	min_ = min;
	current_ = max;
	modifier_ = modifier;
}

Gauge::Gauge ( int max, int min, double current, double modifier )
{
	max_ = max;
	min_ = min;
	current_ = current;
	modifier_ = modifier;
}


Gauge::~Gauge ()
{

}


//------------------------------------------------- Public methods


//--------------------------------------GETTERS

int Gauge::getMax()
{
	return max_;
}

int Gauge::getMin()
{
	return min_;
}

double Gauge::getCurrent()
{
	return current_;
}

double Gauge::getModifier()
{
	return modifier_;
}



//--------------------------------------SETTERS

void Gauge::setCurrent( double value )
{
	if ( value > max_ )
	{
		current_ = max_;
	}
	else if ( value < min_ )
	{
		current_ = min_;
	}
	else
	{
		current_ = value;
	}

}

void Gauge::setModifier( double value )
{
	modifier_ = value;
}

void Gauge::fill()
{
	this->setCurrent(max_);
}

void Gauge::empty()
{
	this->setCurrent(min_);
}

void Gauge::update()
{
	current_ += modifier_;
}
