#ifndef _LUA_HANDLER_H_
#define _LUA_HANDLER_H_

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

// The number of Lua operations allowed per turn
#define MAX_COUNT 100000

#define COUNT_STEP 1000

/** LuaHandler : Objet contenant une instance d'une VM LUA pour executer des scripts
*	
*	@author : Espeute Clément
*/
class LuaHandler
{
public:

	/** Types de retours disponibles pour certaines fonctions de la classe
	*/
	enum ExecutionStatus
	{
		OK				= 1, // Tout c'est bien passé
		ES_ERROR		= 0, // Erreur d'execution
		TOO_MANY_LINES	= -1 // Trop de lignes lues (surement une boucle infinie)
	};

	/** Constructeur d'un LuaHandler
	*/
	LuaHandler();

	// Détruire le LuaHandler
	~LuaHandler();

	/** Charge un script et l'execute une première fois.
	*/
	ExecutionStatus LoadFile(const char* filename);

	/** Execute la fonction "main" d'un fichier script chargé précédemment
	*/
	ExecutionStatus Execute();

	void RegisterFunction(lua_CFunction function, char* nom);

		/* Set a field in a lua table (this lua table must be at the
	top of the stack*/
	static void SetField (lua_State* L, const char *index, float value);

private:
	lua_State *luaState;
	static void LineHookFunc(lua_State *L, lua_Debug *ar);
	lua_State* CreateBasicLua();



	static int lua_CustomPrint(lua_State* L);
	
	static bool tooManyLines;

	// Set to true if the robot has encountered an error
	bool invalid;
};


#endif