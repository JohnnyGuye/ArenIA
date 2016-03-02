#pragma once

#include "GameTimeDuration.h"
#include "GameTimeMoment.h"

class GameTime : 
	public GameTimeDuration, public GameTimeMoment
{
public:

	GameTime(const unsigned int& moment, const unsigned int& duration = 0)
		: GameTimeMoment(moment), GameTimeDuration(duration)
	{
	}

	GameTime(const GameTimeMoment&  gtm = GameTimeMoment(0), const GameTimeDuration& gtd = GameTimeDuration(0))
		: GameTimeMoment(gtm), GameTimeDuration(gtd)
	{
	}

	GameTime(const GameTime& gt)
		: GameTimeMoment(gt.moment_), GameTimeDuration(gt.duration_)
	{
	}

	inline virtual bool operator==(const GameTime& gt) const
	{
		return ((gt.duration_ == duration_ ) && (gt.moment_ == moment_));
	}

	inline virtual bool operator!=(const GameTime& gt) const
	{
		return !(*this == gt);
	}

	inline virtual bool IsNull() const
	{
		return(GameTimeDuration::IsNull() && GameTimeMoment::IsNull());
	}

	virtual ~GameTime(void)
	{
	}
};

