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

/**lua move():void
	@desc Gives the robot the order to move
	@example How to move
	function main()
		move()
		-- Now the robot will move in a straight line
	end
	!eend
*/
int RobotLuaBinding::lua_Robot_move(lua_State *L)
{
	theRobot->move();
	return 0;
}

/**lua fire():void
	@desc Gives the robot the order to fire his gun in front of him
	@example How to fire
	function main()
		fire()
		-- Now the robot will fire
	end
	!eend
*/
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

/**lua turnRobot(angle:double):void
	@desc Gives the robot the order to turn at a certain angle
	@param angle:double The angle in degree that the robot has to turn. A positive angle means he will turn anti-clockwise, and a negative one means he will turn anti-clockwise.
	@example How to turn
	function main()
		turn(50)
		-- Now the robot will turn in order to have a angle of 50 degres
	end
	!eend
*/
int RobotLuaBinding::lua_Robot_turnRobot(lua_State *L)
{
	double angle = luaL_checknumber(L,1);
	theRobot->turnDirection(Ogre::Degree(Ogre::Real(angle)));
	return 0;
}

/**lua turnTurret(angle:double):void
	@desc Gives the robot the order to turn his turret at a certain angle
	@param angle:double The angle in degree that the turret has to turn. A positive angle means he will turn anti-clockwise, and a negative one means he will turn anti-clockwise.
*/
int RobotLuaBinding::lua_Robot_turnTurret(lua_State *L)
{
	double angle = luaL_checknumber(L,1);
	theRobot->turnTurret(Ogre::Degree(Ogre::Real(angle)));
	return 0;
}

/**lua getTurretAngle():double
	@desc Gives you the angle that the robot's turret is facing, relative to the (trouver par rapport à quoi on mesure)
	@return A double corresponding to the angle that the robot's turret is facing
*/
int RobotLuaBinding::lua_Robot_getTurretAngle(lua_State *L)
{
	lua_pushnumber(L,theRobot->getOrientation().valueDegrees());
	return 1;
}

/**lua getRobotAngle():double
	@desc Gives you the angle that the robot is facing, relative to the (trouver par rapport à quoi on mesure)
	@return A double corresponding to the angle that the robot is facing
*/
int RobotLuaBinding::lua_Robot_getRobotAngle(lua_State *L)
{
	lua_pushnumber(L,theRobot->getOrientation().valueDegrees());
	return 1;
}



Robot* RobotLuaBinding::theRobot = nullptr;