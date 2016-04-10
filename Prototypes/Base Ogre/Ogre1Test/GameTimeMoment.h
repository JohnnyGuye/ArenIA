#pragma once

#include "GameTimeDuration.h"

class GameTimeMoment
{
public:

	GameTimeMoment(const int& round = 0)
		: moment_(round)
	{
	}

	GameTimeMoment(const GameTimeMoment& gtm)
		: moment_(gtm.moment_)
	{
	}

	virtual ~GameTimeMoment(void)
	{
	}

	inline virtual int getRound(){	return moment_;	}
	inline virtual int getTimeMilisecond(){	return moment_ * ROUND_IN_MS;	}

	// Self operator
	inline virtual GameTimeMoment&	operator+=(const int& num)
	{
		moment_+=num;
		if(moment_ < 0) moment_ = 0;
		return *this;
	}

	inline virtual GameTimeMoment&	operator-=(const int& num)
	{
		return (*this+=-num);
	}

	/** Create a GameTimeDuration object with a duration 
	*	the time between the two GameTimeMoments 
	inline virtual GameTimeDuration operator-(const GameTimeMoment& gtm) const 
	{	
		return GameTimeDuration(moment_ - gtm.moment_);	
	}

	Same as operator- 
	inline virtual GameTimeDuration operator+(const GameTimeMoment& gtm) const
	{
		return GameTimeDuration(moment_ - gtm.moment_);	
	}
	*/

	inline virtual GameTimeMoment	operator+(const int& num) const
	{
		GameTimeMoment gtm = *this;
		gtm+=num;
		return gtm;
	}
	
	inline virtual GameTimeMoment	operator-(const int& num) const
	{
		GameTimeMoment gtm = *this;
		gtm-=num;
		return gtm;
	}
	
	inline virtual bool				operator==(const GameTimeMoment& gtm) const 
	{
		return (gtm.moment_ == moment_);
	}

	inline virtual bool				operator!=(const GameTimeMoment& gtm) const 
	{
		return !(*this == gtm);
	}

	inline virtual bool				operator==(const int& num) const 
	{
		return num == moment_;
	}

	inline virtual bool				operator!=(const int& num) const
	{
		return !(*this == moment_);
	}

	inline virtual bool IsNull() const
	{
		return moment_ == 0;
	}

public:
	static const int SEC_IN_ROUNDS = 60;
	static const int ROUND_IN_MS = 16667;

protected:
	int moment_;
};

