#include "Gauge.h"

Gauge operator+(Gauge const& lhs, Gauge const& rhs)
{
	Gauge g = lhs;
	g += rhs;
	return g;
}

Gauge operator-(Gauge const& lhs, Gauge const& rhs)
{
	Gauge g = lhs;
	g -= rhs;
	return g;
}

Gauge& Gauge::operator+=(Gauge const& rhs)
	{
		this->max_ += (rhs.max_ - rhs.min_);
		this->current_ += rhs.current_;
		return *this;
	}

Gauge& Gauge::operator-=(Gauge const& rhs)
{
	if(max_-min_ < rhs.max_-rhs.min_) return *this;

	max_ -= (rhs.max_ - rhs.min_);
	current_ -= rhs.current_;
	return *this;
}