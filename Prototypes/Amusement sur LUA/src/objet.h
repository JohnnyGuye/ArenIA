#ifndef OBJET_H
#define OBJET_H
#include <iostream>
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
  }

class Objet
{
public:
	inline void method(){
		i++;
	}
	

	inline void print(){
		std::cout << "Objet : "<< i << std::endl;
	}

	Objet(int i);
private:
	int i;
};

// Classe statique qui permet d'interfacer le lua avec un membre de Objet
class ObjetLuaInterface
{
public:
	static inline void setObjet(Objet *obj) {theObj = obj;} ;
	static int luaCall_method (lua_State *L);
private:
	ObjetLuaInterface();
	static Objet *theObj;
};


#endif