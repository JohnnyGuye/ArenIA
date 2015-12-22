#include "objet.h"

Objet *ObjetLuaInterface::theObj = NULL;

int ObjetLuaInterface::luaCall_method (lua_State *L)
{
	std::cout <<"coucou on m'a appelé" << std::endl;
	theObj->method();
	return 0;
}

Objet::Objet(int i):i(i){};