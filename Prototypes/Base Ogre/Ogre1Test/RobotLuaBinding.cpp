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
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_useAbility,"useAbility");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_getStats,"getStats");

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


/**lua useAbility(id:int):bool
	@desc Use the ability with the given id
	@param id An int corresponding to the number of the ability to use. Call getKnownAbilities in order to know what abilities are aviable
	@return A bool that is true if the robot has an ability for that index, and false otherwise
*/
int RobotLuaBinding::lua_Robot_useAbility(lua_State *L)
{
	unsigned int id = luaL_checknumber(L,1);
	bool hasAbility = theRobot->useAbility(id);
	
	lua_pushnumber(L,hasAbility);
	return 1;
}

/**lua getStats():table
	@desc Get the currents and max stats of your robot in a lua table.
	the lua table contains these fields
	<ul>
		<li>maxHp : The max hp of your robot </li>
		<li>maxHp : The max hp of your robot</li>
		<li>maxEnergy : The max Energy of your robot</li>
		<li>currentEnergy : The current Energy of your robot </li>
		<li>range : The range of your weapon</li>
		<li>resistance : The armor of your robot</li>
		<li>speed : The speed of your robot</li>
	</ul>
	@example How to use getStats()
	function main()
		-- Get the stats
		stats = getStats()

		-- Use them
		if (stats.currentHP < 10) then
			-- ...
		end
	end
	!eend
*/
int RobotLuaBinding::lua_Robot_getStats(lua_State *L)
{
	lua_newtable(L);
	Stats stats = theRobot->getFullStats();

	LuaHandler::SetField(L, "maxHP", stats.hp.getMax());
	LuaHandler::SetField(L, "currentHP", stats.hp.getCurrent());

	LuaHandler::SetField(L, "maxEnergy", stats.energy.getMax());
	LuaHandler::SetField(L, "currentEnergy", stats.energy.getCurrent());

	LuaHandler::SetField(L, "currentVisionAngle", stats.visionAngle.getCurrent());
	LuaHandler::SetField(L, "maxVisionAngle", stats.visionAngle.getMax());
	LuaHandler::SetField(L, "minVisionAngle", stats.visionAngle.getMin());
	
	LuaHandler::SetField(L, "range", stats.range);
	LuaHandler::SetField(L, "resistance", stats.resistance);
	LuaHandler::SetField(L, "speed", stats.speed);
	
	
	


	return 1;
}




Robot* RobotLuaBinding::theRobot = nullptr;