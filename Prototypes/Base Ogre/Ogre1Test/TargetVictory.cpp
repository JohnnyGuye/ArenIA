#include "TargetVictory.h"


TargetVictory::TargetVictory(const int& targetID)
	: VictoryHandler(), targetID_(targetID)
{
	eventsToHandle_.insert(GameEvent::EventType::ROBOT_KILL);
	createFlag("killed");
}

TargetVictory::~TargetVictory(void)
{
}

void TargetVictory::updateFlags()
{
	GameEvent* ge = events_.back();
	switch(ge->getEventType())
	{
	case GameEvent::EventType::ROBOT_KILL:
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