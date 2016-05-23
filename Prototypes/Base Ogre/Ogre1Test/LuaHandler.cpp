#include "LuaHandler.h"
#include "RobotLuaBinding.h"
#include "Log.h"

bool LuaHandler::tooManyLines = false;
// Permet de compter le nombre d'instructions exécutées par le script lua
void LuaHandler::LineHookFunc(lua_State *L, lua_Debug *ar)
{
    if(ar->event == LUA_HOOKCOUNT)
    {
      LuaHandler::currentHandlerLineCount ++;
      if (LuaHandler::currentHandlerLineCount >MAX_COUNT/COUNT_STEP)
	  {
		tooManyLines = true;
        luaL_error(L, "Too Many Lines Error");
	  }
    }
            
}


static int traceback(lua_State *L) {
    lua_getfield(L, LUA_GLOBALSINDEX, "debug");
    lua_getfield(L, -1, "traceback");
    lua_pushvalue(L, 1);
    lua_pushinteger(L, 2);
    lua_call(L, 2, 1);
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    return 1;
}


lua_State* LuaHandler::CreateBasicLua()
{
    lua_State *L;

    L = luaL_newstate();
    if (L) {
        lua_pushcfunction(L, luaopen_base);
        lua_pushstring(L, "");
        lua_call(L, 1, 0);
        lua_pushcfunction(L, luaopen_math);
        lua_pushstring(L, LUA_LOADLIBNAME);
        lua_call(L, 1, 0);

		// Customize the print function :
		static const struct luaL_Reg printlib [] = {
				  {"print", LuaHandler::lua_CustomPrint},
				  {NULL, NULL} /* end of array */
				};

		lua_getglobal(L, "_G");
		luaL_register(L, NULL, printlib);
		lua_pop(L, 1);

		lua_pushcfunction(L, traceback);

    }
    return L;
}

LuaHandler::ExecutionStatus LuaHandler::LoadFile(const char* filename)
{
	int ret = luaL_loadfile(luaState, filename);
    

	lua_pcall(luaState,0,0,0);

	  if(ret != 0){
		ArenIA::Log::getInstance()->write("ERREUR : Impossible d'ouvrir le ficher :");
		ArenIA::Log::getInstance()->write(filename);
		ArenIA::Log::getInstance()->write(lua_tostring(luaState, -1));
		ArenIA::Log::getInstance()->write("\n");

	    return ES_ERROR;
	  }

	  return OK;
}


LuaHandler::ExecutionStatus LuaHandler::Execute()
{
	if ( ! invalid)
	{
		tooManyLines = false;
		lua_getglobal(luaState, "main");
		
		// Reset the line count
		LuaHandler::currentHandlerLineCount = 0;
		if (lua_pcall(luaState,0,0,0) != 0)
		{
			//ArenIA::Log::getInstance()->write("ERREUR : Execution LUA échouée :");
			//ArenIA::Log::getInstance()->write(lua_tostring(luaState, -1));
			std::cout << "ERREUR : Execution LUA : " << lua_tostring(luaState, -1) << std::endl;
			
			invalid = true;
			if (tooManyLines)
			{
				return TOO_MANY_LINES;
			}
			return ES_ERROR;
		}
		return OK;
	}
	return TOO_MANY_LINES;
}

void LuaHandler::RegisterFunction(lua_CFunction function, char* nom)
{
    lua_register(luaState, nom, function);
}

/* assume that table is at the top */
void LuaHandler::SetField (lua_State* L, const char *index, float value) {
    lua_pushstring(L, index);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}


LuaHandler::LuaHandler()
	: invalid(false)
{
	luaState = CreateBasicLua();
	lua_sethook(luaState, &LuaHandler::LineHookFunc, LUA_MASKCOUNT, COUNT_STEP);
	RobotLuaBinding::bindFunctions(this);
}

LuaHandler::~LuaHandler()
{
	lua_close(luaState);
}

int LuaHandler::lua_CustomPrint(lua_State* L) {
    int nargs = lua_gettop(L);

    for (int i=1; i <= nargs; i++) {
        if (lua_isstring(L, i)) {
            const char* string = lua_tostring(L, i);
			std::cout << string << std::endl;
		}
        else {
        /* Do something with non-strings if you like */
        }
    }
	//std::cout << "Yay" << std::endl;
	std::cout.flush();
    return 0;
}

long int LuaHandler::currentHandlerLineCount = 0;