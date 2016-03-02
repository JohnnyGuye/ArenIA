#include "FightManager.h"

using namespace std;

FightManager::FightManager(const std::string& mapFileName, VictoryHandler* vo)
	: day_(60 * 60, 0, 0.0, 1.0), roundAfterSD_(0), victoryHandler_(vo)
{
	loadTerrain(mapFileName);
}

FightManager::~FightManager(void)
{
	while(events_.size() > 0)
	{
		delete *(events_.begin());
		events_.pop_front();
	}

	while(objects_.size() > 0)
	{
		delete *(objects_.begin());
		objects_.pop_front();
	}

	if(victoryHandler_)	delete victoryHandler_;
}

void FightManager::loadTerrain(const string& fileName)
{
	terrain_ = new Terrain(fileName);
}

GameTime FightManager::getTime() const
{
	return GameTime((int)day_.getCurrent());
}

void FightManager::addEvent(GameEvent* ge)
{
	events_.push_back(ge);
	victoryHandler_->handleEvent(ge);
}

bool FightManager::IsVictory() const
{
	return (victoryHandler_->IsVictory());
}

//TODO implement update
void FightManager::update()
{
	
	day_.update();
	if(day_.IsFull())
	{
		if(roundAfterSD_ == 0)
			addEvent(new StartSDEvent(getTime()));
		roundAfterSD_++;
	}
}

//TODO implement reset
void FightManager::reset()
{
	addEvent(new GameEvent(GameEvent::RESET_TIMER));
	day_.empty();
}

double FightManager::getActualTime() const
{
	return day_.getFilledAbsolute();
}

double FightManager::getRemainingTime() const
{
	return day_.getNotFilledAbsolute();
}

Terrain* FightManager::getTerrain() const
{
	return terrain_;
}
