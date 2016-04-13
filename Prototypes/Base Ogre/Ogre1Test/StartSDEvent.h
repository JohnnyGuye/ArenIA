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

	inline friend std::ostream& operator<<( std::ostream &lhs, const StartSDEvent& rhs)
	{
		lhs << rhs.getTime().getRound() << " - ";
		lhs << "Sudden Death";
		return lhs;
	}
};

