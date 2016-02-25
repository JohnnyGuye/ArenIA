#include "TeamKillVictory.h"


TeamKillVictory::TeamKillVictory(void)
	: VictoryHandler()
{
	eventsToHandle_.insert(GameEvent::EventType::TEAM_KILL);
	createFlag("teamkilled");
}

TeamKillVictory::~TeamKillVictory(void)
{
}

void TeamKillVictory::updateFlags() 
{
	GameEvent* ge = events_.back();
	switch(ge->getEventType())
	{
	case GameEvent::EventType::TEAM_KILL:
		{
			TeamKillEvent* tke = (TeamKillEvent*)ge;
			if(tke->getTeamID() == teamID_)
				setFlag("teamkilled");
		}
		break;
	default:
		break;
	}
}