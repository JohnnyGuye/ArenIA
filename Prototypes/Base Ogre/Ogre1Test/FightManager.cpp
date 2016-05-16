#include "FightManager.h"
#include "WasheeRobot.h"
#include "MowerRobot.h"
#include "Log.h"
#include "RobotLuaBinding.h"

using namespace std;

template <typename T>
void destroyList(std::list<T> rhs)
{
	while(rhs.size() > 0)
	{
		delete (rhs.front());
		rhs.pop_front();
	}
}

FightManager::FightManager(const std::string& mapFileName, VictoryHandler* vo)
	: day_(60 * 60, 0, 0.0, 1.0), roundAfterSD_(0), victoryHandler_(vo)
{
	loadTerrain(mapFileName);
	
	// Init the RobotLuaHandler
	RobotLuaBinding::setFight(this);

	list<Ogre::Vector3> starts = getTerrain()->getStarts();
	int i = 0;
	for(std::list<Ogre::Vector3>::iterator it = starts.begin(); it != starts.end() ; it++ )
	{
		ArenIA::Log::getInstance()->write("Robot created !");
		std::stringstream ss;
		ss << "Robot-" << (i > 9 ? "0" : "00") << i++;
		if(i%2)	addRobot(new WasheeRobot(*it, ss.str(), Robot::NONE));
		else	addRobot(new MowerRobot(*it, ss.str(), Robot::NONE));
	}
}

FightManager::~FightManager(void)
{
	destroyList(events_);
	destroyList(objects_);
	destroyList(missiles_);
	destroyList(missilesBeforeRender_);
	destroyList(robots_);

	if(victoryHandler_)	delete victoryHandler_;
}

void FightManager::loadTerrain(const string& fileName)
{
	terrain_ = new Terrain(fileName);
}

void FightManager::addRobot(Robot* robot)
{
	robot->setFightManager(this);
	robots_.push_back(robot);
}

void FightManager::addMissile(Missile* missile)
{
	missiles_.push_back(missile);
	missilesBeforeRender_.push_back(missile);
}

Missile* FightManager::renderLastQueuedMissile(void)
{
	Missile* m = nullptr;
	if( missilesBeforeRender_.size() > 0)
	{
		m = missilesBeforeRender_.front();
		missilesBeforeRender_.pop_front();
	}
	return m;
}

GameTime FightManager::getTime() const
{
	return GameTime((int)day_.getCurrent());
}

void FightManager::addEvent(GameEvent* ge)
{
	std::stringstream ss;
	switch(ge->getEventType())
	{
	case GameEvent::START_SD:
		{
		StartSDEvent* cge = (StartSDEvent*)ge;
		ss << *cge;
		break;
		}
	default:
		ss << *ge;
	}
	
	ArenIA::Log::getInstance()->write(ss.str());
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
	//updating robots
	for(list<Robot*>::iterator it = robots_.begin() ; it != robots_.end() ; it++)
	{
		(*it)->update();
	}

	//Applying collision
	for(list<Robot*>::iterator it = robots_.begin() ; it != robots_.end() ; it++)
	{
		(*it)->applyUpdate(terrain_->getCollision(*it, true));
	}

	//Updating missiles
	for(auto it = missiles_.begin() ; it != missiles_.end() ; )
	{
		auto m = *it;
		m->update();
		
		if(terrain_->getCollision(m))
		{
			it = missiles_.erase(it);
			m->kill();
		}
		else
		{
			//Collision with robots
			bool asCollided = false;
			for(auto rIt = robots_.begin() ; rIt != robots_.end() ; rIt++)
			{
				//m->getHitbox()->intersect((*it)->get
			}

			if(asCollided)
			{
				it = missiles_.erase(it);
				m->kill();
			}
			else
			{
				it++;
			}
		}
	}

	//updating the day
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

float FightManager::getActualTime() const
{
	return day_.getFilledAbsolute();
}

float FightManager::getRemainingTime() const
{
	return day_.getNotFilledAbsolute();
}

float FightManager::getDayRatio() const
{
	return day_.getRatio();
}

Terrain* FightManager::getTerrain() const
{
	return terrain_;
}

Robot* FightManager::getRobot(unsigned int id) const
{
	for (std::list<Robot*>::const_iterator iterator = robots_.begin(); iterator != robots_.end(); ++iterator)
	{
		if ((*iterator)->getId() == id)
		{
			return *iterator;
		}
	}
	return nullptr;
}

std::list<Robot*> FightManager::getRobots() const
{
	return robots_;
}

std::list<Missile*> FightManager::getMissiles() const
{
	return missiles_;
}