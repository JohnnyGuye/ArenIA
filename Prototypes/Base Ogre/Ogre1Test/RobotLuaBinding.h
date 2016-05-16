#ifndef _ROBOT_LUA_BINDING_H_
#define _ROBOT_LUA_BINDING_H_

#include "Robot.h"
#include "LuaHandler.h"
#include "FightManager.h"

class RobotLuaBinding {
public:
	inline RobotLuaBinding() {};
	inline ~RobotLuaBinding() {};

	static void setRobot(Robot* robot);
	static void setFight(FightManager* fight);

	static void bindFunctions(LuaHandler* handler);
private:
	static Robot* theRobot;
	static FightManager* theFight;

	static int lua_Robot_move(lua_State *L);
	static int lua_Robot_fire(lua_State *L);
	static int lua_Robot_turnRobot(lua_State *L);
	static int lua_Robot_turnTurret(lua_State *L);

	static int lua_Robot_getTurretAngle(lua_State *L);
	static int lua_Robot_getRobotAngle(lua_State *L);

	static int lua_Robot_useAbility(lua_State *L);

	static int lua_Robot_getStats(lua_State *L);
	static int lua_Robot_getTeam(lua_State *L);
	static int lua_Robot_getState(lua_State *L);
	static int lua_Robot_getRobots(lua_State *L);
	static int lua_Robot_debugTurn(lua_State *L);
		
};

#endif