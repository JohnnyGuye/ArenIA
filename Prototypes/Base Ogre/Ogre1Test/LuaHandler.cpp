#include "LuaHandler.h"
#include "RobotLuaBinding.h"
#include "Log.h"

// Permet de compter le nombre d'instructions exécutées par le script lua
void LuaHandler::LineHookFunc(lua_State *L, lua_Debug *ar)
{
    if(ar->event == LUA_HOOKCOUNT)
    {
      static int i = 0;
      i ++;
      if (i>1500)
        luaL_error(L, "Too Many Lines Error");
    }
            
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
		ArenIA::Log::getInstance()->write("\n");
	    return ES_ERROR;
	  }

	  return OK;
}

LuaHandler::ExecutionStatus LuaHandler::Execute()
{
    lua_getglobal(luaState, "main");
    if (lua_pcall(luaState,0,0,0) != 0)
	{
		ArenIA::Log::getInstance()->write("ERREUR : Execution LUA échouée :");
		ArenIA::Log::getInstance()->write(lua_tostring(luaState, -1));
		return ES_ERROR;
	}
	return OK;
}

void LuaHandler::RegisterFunction(lua_CFunction function, char* nom)
{
    lua_register(luaState, nom, function);
}


LuaHandler::LuaHandler()
{
	luaState = CreateBasicLua();
	lua_sethook(luaState, &LuaHandler::LineHookFunc, LUA_MASKCOUNT, 15);
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
	std::cout << "Yay" << std::endl;
	std::cout.flush();
    return 0;
}