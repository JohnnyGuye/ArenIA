#pragma once
#include "GameEvent.h"
class StartSDEvent :
	public GameEvent
{
public:

	StartSDEvent(const GameEvent& gt)
		: GameEvent(gt)
	{
	}

	virtual ~StartSDEvent(void){}
	
	inline virtual EventType		getEventType() const {	return START_SD;	}
};

