#pragma once

#include "Terrain.h"
#include <string>

class FightManager
{
public:
	FightManager(void);
	virtual ~FightManager(void);

	virtual void loadTerrain(const std::string& fileName);
	virtual Terrain* getTerrain() const;

protected:

	Terrain *terrain_;
};

