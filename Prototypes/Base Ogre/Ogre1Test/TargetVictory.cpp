#include "TargetVictory.h"


TargetVictory::TargetVictory(const int& targetID)
	: VictoryHandler(), targetID_(targetID)
{
	eventsToHandle_.insert(GameEvent::ROBOT_KILL);
	createFlag("killed");
}

TargetVictory::~TargetVictory(void)
{
}

void TargetVictory::updateFlags(void)
{
	GameEvent* ge = events_.back();
	switch(ge->getEventType())
	{
	case GameEvent::ROBOT_KILL:
		{
			RobotKillEvent* rke = (RobotKillEvent*)ge;
			if(rke->getVictimId() == targetID_)
				setFlag("killed");
		}
		break;
	default:
		break;
	}
}