#include "TeamKillVictory.h"


TeamKillVictory::TeamKillVictory(void)
	: VictoryHandler()
{
	eventsToHandle_.insert(GameEvent::TEAM_KILL);
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
	case GameEvent::TEAM_KILL:
		{
			TeamKillEvent* tke = (TeamKillEvent*)ge;
			if(tke->getTeamId() == teamID_)
				setFlag("teamkilled");
		}
		break;
	default:
		break;
	}
}