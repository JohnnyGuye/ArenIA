#include "EndOfDayVictory.h"


EndOfDayVictory::EndOfDayVictory(void)	
{
	eventsToHandle_.insert(GameEvent::START_SD);
	this->createFlag("dayEnd");
}


EndOfDayVictory::~EndOfDayVictory(void)
{
}

void EndOfDayVictory::updateFlags(void)
{
	GameEvent* ge = events_.back();
	switch(ge->getEventType())
	{
	case GameEvent::START_SD:
		{
			setFlag("dayEnd");
		}
		break;
	default:
		break;
	}
}
