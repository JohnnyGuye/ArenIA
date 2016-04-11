#include "RobotLuaBinding.h"
#include <OgreMath.h>

void RobotLuaBinding::setRobot(Robot* robot)
{
	theRobot = robot;
}

void RobotLuaBinding::bindFunctions(LuaHandler* handler)
{
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_move,"move");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_fire,"fire");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_debugTurn,"debugTurn");
}

int RobotLuaBinding::lua_Robot_move(lua_State *L)
{
	theRobot->move();
	return 0;
}

int RobotLuaBinding::lua_Robot_fire(lua_State *L)
{
	theRobot->fire();
	return 0;
}

int RobotLuaBinding::lua_Robot_debugTurn(lua_State *L)
{
	theRobot->resetAction();
	theRobot->turnDirection(Ogre::Degree(1));
	return 0;
}

Robot* RobotLuaBinding::theRobot = nullptr;