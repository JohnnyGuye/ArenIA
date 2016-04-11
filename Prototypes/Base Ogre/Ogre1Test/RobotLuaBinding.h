#ifndef _ROBOT_LUA_BINDING_H_
#define _BOBOT_LUA_BINDING_H_

#include "Robot.h"
#include "LuaHandler.h"

class RobotLuaBinding {
public:
	inline RobotLuaBinding() {};
	inline ~RobotLuaBinding() {};

	static void setRobot(Robot* robot);

	static void bindFunctions(LuaHandler* handler);
private:
	static Robot* theRobot;

	static int lua_Robot_move(lua_State *L);
	static int lua_Robot_fire(lua_State *L);
	static int lua_Robot_debugTurn(lua_State *L);
};

#endif