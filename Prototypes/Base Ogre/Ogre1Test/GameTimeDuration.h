#pragma once


/*
* This source file is a part of the 
*           ______                                  ___   ______
*          /      |                                |   | |      \
*         /       |                                |   | |       \
*        /        |                                |   | |        \
*       /    /|   |  ______     _______   __   __  |   | |   |\    \
*      /    / |   | |      \   |   ____| |  \ |  | |   | |   | \    \
*     /    /__|   | |  |)   |  |  |__    |   \|  | |   | |   |__\    \
*    /    ____    | |      /   |   __|   |       | |   | |    ___     \
*   /    /    |   | |   _  \   |  |      |       | |   | |   |    \    \
*  /    /     |   | |  | \  \  |  |____  |  |\   | |   | |   |     \    \
* /____/      |___| |__|  \__\ |_______| |__| \__| |___| |___|      \____\ project
* 
* Copyright (c) 2016-2017
*
* @author Johnny Guye
* @summary : This class represent a duration of time in the game
*/


#include "GameTimeMoment.h"

class GameTimeDuration
{
public:

	GameTimeDuration(const int& rounds = 0)
		: duration_(rounds)
	{
	}

	virtual ~GameTimeDuration(void)
	{
	}

	/* Inheritance */
	inline virtual int getDuration(){	return duration_;	}
	inline virtual int getDurationMilisecond(){	return duration_ * ROUND_IN_MS;	}

	// Self operators
	inline virtual GameTimeDuration& operator+=(const GameTimeDuration& gtd)
	{
		duration_+=gtd.duration_;
		return *this;
	}

	inline virtual GameTimeDuration& operator-=(const GameTimeDuration& gtd)
	{	
		int d = gtd.duration_ - duration_;
		duration_ = (d >= 0 ? d : -d);
		return *this;
	}

	inline virtual GameTimeDuration& operator*=(const int& num)
	{
		duration_*=num;
		return *this;
	}

	inline virtual GameTimeDuration& operator/=(const int& num)
	{
		duration_/=num;
		return *this;
	}

	// Other operators
	inline virtual GameTimeDuration operator+(const GameTimeDuration& gtd) const 
	{
		GameTimeDuration gtd1 = *this;
		gtd1+=gtd;
		return gtd1;
	}

	inline virtual GameTimeDuration operator-(const GameTimeDuration& gtd) const 
	{
		GameTimeDuration gtd1 = *this;
		gtd1-=gtd;
		return gtd1;
	}

	inline virtual GameTimeDuration operator*(const int& num) const 
	{
		GameTimeDuration gtd1 = *this;
		gtd1*=num;
		return gtd1;
	}

	inline virtual GameTimeDuration operator/(const int& num) const 
	{
		GameTimeDuration gtd1 = *this;
		gtd1/=num;
		return gtd1;
	}

	inline virtual GameTimeDuration& operator=(const GameTimeDuration& gtd)
	{
		duration_ = gtd.duration_;
		return *this;
	}

	inline virtual bool operator==(const GameTimeDuration& gtd) const 
	{
		return (gtd.duration_ == duration_);
	}

	inline virtual bool operator!=(const GameTimeDuration& gtd) const 
	{
		return !(*this == gtd);
	}

	inline virtual bool operator==(const int& num) const 
	{
		return duration_ == num;
	}

	inline virtual bool operator!=(const int& num) const 
	{
		return !(*this == num);
	}

	inline virtual bool IsNull() const
	{
		return (duration_ == 0);
	}

public:
	static const int SEC_IN_ROUNDS = GameTimeMoment::SEC_IN_ROUNDS;
	static const int ROUND_IN_MS = GameTimeMoment::ROUND_IN_MS;
	
protected:
	int duration_;
};

