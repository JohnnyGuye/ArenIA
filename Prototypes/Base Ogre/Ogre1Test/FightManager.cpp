#include "FightManager.h"

using namespace std;

FightManager::FightManager(const std::string& mapFileName)
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
}

void FightManager::loadTerrain(const string& fileName)
{
	terrain_ = new Terrain(fileName);
}

GameTime FightManager::getTime() const
{
	return GameTime(round_);
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
	round_++;
}

//TODO implement reset
void FightManager::reset()
{
	addEvent(new GameEvent(GameEvent::EventType::RESET_TIMER));
	round_ = 0;
}

Terrain* FightManager::getTerrain() const
{
	return terrain_;
}
