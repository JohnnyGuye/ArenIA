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
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_turnRobot,"turnRobot");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_turnTurret,"turnTurret");

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
	theRobot->turnDirection(Ogre::Degree(1));
	return 0;
}

int RobotLuaBinding::lua_Robot_turnRobot(lua_State *L)
{
	double angle = luaL_checknumber(L,1);
	theRobot->turnDirection(Ogre::Degree(Ogre::Real(angle)));
	return 0;
}

int RobotLuaBinding::lua_Robot_turnTurret(lua_State *L)
{
	double angle = luaL_checknumber(L,1);
	theRobot->turnTurret(Ogre::Degree(Ogre::Real(angle)));
	return 0;
}

int RobotLuaBinding::lua_Robot_getTurretAngle(lua_State *L)
{
	lua_pushnumber(L,theRobot->getOrientation().valueDegrees());
	return 1;
}

int RobotLuaBinding::lua_Robot_getRobotAngle(lua_State *L)
{
	lua_pushnumber(L,theRobot->getOrientation().valueDegrees());
	return 1;
}



Robot* RobotLuaBinding::theRobot = nullptr;