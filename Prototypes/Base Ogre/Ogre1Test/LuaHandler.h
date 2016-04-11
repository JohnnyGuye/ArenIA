#ifndef _LUA_HANDLER_H_
#define _LUA_HANDLER_H_

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

class LuaHandler
{
public:
	enum ExecutionStatus
	{
		OK = 1,
		ES_ERROR = 0,
		TOO_MANY_LINES = -1
	};

	// Créer le LuaHandler
	LuaHandler();

	// Détruire le LuaHandler
	~LuaHandler();

	ExecutionStatus LoadFile(const char* filename);

	ExecutionStatus Execute();

	void RegisterFunction(lua_CFunction function, char* nom);
private:
	lua_State *luaState;
	static void LineHookFunc(lua_State *L, lua_Debug *ar);
	lua_State* CreateBasicLua();

	static int lua_CustomPrint(lua_State* L);
	
};


#endif