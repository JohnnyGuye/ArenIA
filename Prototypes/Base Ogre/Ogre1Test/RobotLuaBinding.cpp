#include "RobotLuaBinding.h"
#include <OgreMath.h>

void RobotLuaBinding::setRobot(Robot* robot)
{
	theRobot = robot;
}

void RobotLuaBinding::setFight(FightManager* fight)
{
	theFight = fight;
}

void RobotLuaBinding::bindFunctions(LuaHandler* handler)
{
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_getTerrainSize,"getTerrainSize");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_getPosition,"getPosition");


	handler->RegisterFunction(RobotLuaBinding::lua_Robot_move,"move");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_fire,"fire");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_turnRobot,"turnRobot");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_turnTurret,"turnTurret");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_useAbility,"useAbility");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_getStats,"getStats");
	handler->RegisterFunction(RobotLuaBinding::lua_Robot_getTeam,"getTeam");

	handler->RegisterFunction(RobotLuaBinding::lua_Robot_debugTurn,"debugTurn");
}

/**lua getTerrainSize():int,int
	@desc Returns the height and the width of the Terrain
*/
int RobotLuaBinding::lua_Robot_getTerrainSize(lua_State *L)
{
	lua_pushnumber(L, Terrain::cellToPos(theFight->getTerrain()->getHeight()));
	lua_pushnumber(L, Terrain::cellToPos(theFight->getTerrain()->getWidth()));
	return 2;
}

/**lua getPosition():double,double
	@desc Returns the current X and Y position of your robot
	@return The X position of your robot
	@return The Y position of your robot
*/
int RobotLuaBinding::lua_Robot_getPosition(lua_State *L)
{
	Robot* robot;
	if (lua_gettop(L) == 0)
	{
		robot = theRobot;
	}
	else
	{
		int id = (int)luaL_checknumber(L,1);
		robot = theFight->getRobot(id);
	}

	lua_pushnumber(L, robot->getPosition().x);
	lua_pushnumber(L, robot->getPosition().z);
	return 2;
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
	unsigned int id = (int)luaL_checknumber(L,1);
	bool hasAbility = theRobot->useAbility(id);
	
	lua_pushnumber(L,hasAbility);
	return 1;
}

/**lua getStats(id:int):table
	@desc Get the currents and max stats of the robot with the given id in a lua table. If no robot is given, your robot is chosen. <br/>
	The lua table contains these fields
	<ul>
		<li>maxHp : The max hp of the robot </li>
		<li>maxHp : The max hp of the robot</li>
		<li>maxEnergy : The max Energy of the robot</li>
		<li>currentEnergy : The current Energy of the robot </li>
		<li>range : The range of the weapon</li>
		<li>resistance : The armor of the robot</li>
		<li>speed : The speed of the robot</li>
	</ul>
	@example How to use getStats()
	function main()
		-- Get the stats of your robot
		stats = getStats()

		-- Get the stats of antother robot
		statsOtherRobot = getStats(1)
		-- Use them
		if (stats.currentHP < 10) then
			-- ...
		end
	end
	!eend
*/
int RobotLuaBinding::lua_Robot_getStats(lua_State *L)
{
	Stats stats;
	if (lua_gettop(L) == 0)
	{
		stats = theRobot->getFullStats();
	}
	else
	{
		int id = (int)luaL_checknumber(L,1);
		stats = theFight->getRobot(id)->getFullStats();
	}
	lua_newtable(L);
	
	
	LuaHandler::SetField(L, "maxHP", (float)stats.hp.getMax());
	LuaHandler::SetField(L, "currentHP", stats.hp.getCurrent());

	LuaHandler::SetField(L, "maxEnergy", (float)stats.energy.getMax());
	LuaHandler::SetField(L, "currentEnergy", stats.energy.getCurrent());

	LuaHandler::SetField(L, "currentVisionAngle", stats.visionAngle.getCurrent());
	LuaHandler::SetField(L, "maxVisionAngle", (float)stats.visionAngle.getMax());
	LuaHandler::SetField(L, "minVisionAngle", (float)stats.visionAngle.getMin());
	
	LuaHandler::SetField(L, "range", (float)stats.range);
	LuaHandler::SetField(L, "resistance", (float)stats.resistance);
	LuaHandler::SetField(L, "speed", stats.speed);

	return 1;
}


/*lua getTeam():int
	@desc Return an int indicating the teams that your robot belongs.
	Each byte of the int correspond to a team. If the bit is set, your robot is in that team
	Else, you are not.
	For references, the team colors are :
	<ul>
		<li>NONE = 0</li>
		<li>BLACK = 1</li>
		<li>WHITE = 2</li>
		<li>BLUE = 4</li>
		<li>PURPLE = 8</li>
		<li>RED = 16</li>
		<li>ORANGE = 32</li>
		<li>YELLOW = 64</li>
		<li>GREEN = 128</li>
	</ul>
*/
int RobotLuaBinding::lua_Robot_getTeam(lua_State *L)
{
	Robot* robot;
	if (lua_gettop(L) == 0)
	{
		robot = theRobot;
	}
	else
	{
		int id = (int)luaL_checknumber(L,1);
		robot = theFight->getRobot(id);
	}

	lua_pushnumber(L, robot->getTeam());
	return 1;
}


/*lua getState():int
	@desc Return an int indicating the current state of the selected robot
*/
int RobotLuaBinding::lua_Robot_getState(lua_State *L)
{
	Robot* robot;
	if (lua_gettop(L) == 0)
	{
		robot = theRobot;
	}
	else
	{
		int id = (int)luaL_checknumber(L,1);
		robot = theFight->getRobot(id);
	}

	lua_pushnumber(L, robot->getState());
	return 1;
}

/*lua getRobots():table
	@desc Returns a table containing the list of all the robots in the game.
	Your robot will always be in the first (1) index.
*/
int RobotLuaBinding::lua_Robot_getRobots(lua_State *L)
{
	std::list<Robot*> robotList = theFight->getRobots();
	int num_robot = robotList.size();

	lua_createtable(L, num_robot, 0);

	// Push our robot as the first element of the list
	unsigned int ourId = theRobot->getId();
	lua_pushinteger(L, ourId);
	int i = 0;
	lua_rawseti (L, -2, i++);
	
	// Push the rest of the robot
	for (std::list<Robot*>::iterator iterator = robotList.begin(); iterator != robotList.end(); iterator++) {
		unsigned int robotId = (*iterator)->getId();
		// If the robot is our robot, skip it
		if (robotId != ourId)
		{
			lua_pushinteger(L, robotId);
			lua_rawseti (L, -2, i++);
		}
	}
	return 1;
}

/**lua isAWall(x:int,y:int):bool
	@desc Tells if there is a wall at the given coordinate.
	@param x The x position of the point where to check
	@param y The y position of the point where to check
	@return True if there is a wall, false if there is no wall
*/
int RobotLuaBinding::lua_Robot_isAWall(lua_State *L)
{
	int x = Terrain.posToCell((int) luaL_checknumber(L,1));
	int y = Terrain.posToCell((int) luaL_checknumber(L,1));

	lua_pushboolean(L, theFight->getTerrain()->IsAWall(x,y);
	return 1;
}


Robot* RobotLuaBinding::theRobot = nullptr;
FightManager* RobotLuaBinding::theFight = nullptr;