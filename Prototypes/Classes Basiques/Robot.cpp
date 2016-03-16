#include "Robot.h"


Robot::Robot(void)
{
}

Robot::~Robot(void)
{
}

Team Robot::getTeam() const
{
	return team_;
}

int Robot::getAction() const
{
	return action_;
}

bool Robot::isMoving() const 
{	
	return action_ == MOVING;	
}

bool Robot::isIDLE() const
{
	return (action_ == IDLE);
}