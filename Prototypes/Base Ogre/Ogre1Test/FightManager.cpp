#include "FightManager.h"

using namespace std;

FightManager::FightManager(void)
{
	loadTerrain("essai1.txt");
}

void FightManager::loadTerrain(const string& fileName)
{
	terrain_ = new Terrain(fileName);
}

FightManager::~FightManager(void)
{
}

Terrain* FightManager::getTerrain() const
{
	return terrain_;
}
