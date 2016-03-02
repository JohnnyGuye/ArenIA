#include "VictoryHandler.h"

using namespace std;

VictoryHandler::VictoryHandler(void)
	: flagsToRaise_(0)
{
}

VictoryHandler::~VictoryHandler(void)
{
}

bool VictoryHandler::handleEvent(GameEvent* ge)
{
	if(eventsToHandle_.find(ge->getEventType()) != eventsToHandle_.end() )
	{
		events_.push_back(ge);
		updateFlags();
		return true;
	}
	return false;
}

void VictoryHandler::createFlag(const string& attr)
{
	flags_.insert(pair<string, bool>(attr, false));
	flagsToRaise_++;
}

void VictoryHandler::setFlag(const string& attr, const bool& state)
{
	FlagsMap::iterator attribute = flags_.find(attr);
	if(attribute != flags_.end())
	{
		if(state && !attribute->second)
			flagsToRaise_--;
		else if(!state && attribute->second)
			flagsToRaise_++;
		attribute->second = state;
	}
}

int VictoryHandler::getFlagsToRaise() const
{
	return flagsToRaise_;
}

bool VictoryHandler::IsVictory() const
{
	for(FlagsMap::const_iterator it = flags_.cbegin(); it != flags_.cend(); it++)
	{
		if(it->second == false)	return false;
	}
	return true;
}