#include <stdio.h>
#include <iostream>
#include <string>
#include "objet.h"
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
  }

using namespace std;

// Hook lua qui permet de "compter" le
// nombre d'opérations effectuées par le script
// lua et d'arreter le programme si il prends trop
// de temps à s'executer
void LineHookFunc(lua_State *L, lua_Debug *ar)
{
    if(ar->event == LUA_HOOKCOUNT)
    {
      //printf("Poulet !\n");
      static int i = 0;
      i ++;
      if (i>1500)
        luaL_error(L, "Too Many Lines Error");
    }
            
}

// Fonction de test avec récupération des arguments
// depuis le stack lua.
int test (lua_State *L)
{
  if(!lua_isstring(L,1))
  {
    lua_pushstring(L, "Incorrect argument to 'test' ");
    lua_error(L);
  }
  string name = lua_tostring(L,1);
  cout << "Hello World " << name << "\n";
  return 0;
}


// Permet de créer une lua_State avec seulement
// Quelques librairies
lua_State *CreateBasicLua() {
    lua_State *L;

    L = luaL_newstate();
    if (L) {
        lua_pushcfunction(L, luaopen_base);
        lua_pushstring(L, "");
        lua_call(L, 1, 0);
        lua_pushcfunction(L, luaopen_math);
        lua_pushstring(L, LUA_LOADLIBNAME);
        lua_call(L, 1, 0);
    }
    return L;
}

void call_laFonction(lua_State *L)
{
  // 
  lua_getglobal(L, "laFonction");
  lua_pcall(L,0,0,0);
}


int main (void) {
  Objet obj(0);
  ObjetLuaInterface::setObjet(&obj);

  obj.print();
  char buff[256];
  int error;
  lua_State *L = CreateBasicLua();   /* opens Lua */

              /* opens the math lib. */
  lua_register(L,"testFunc",test);
  lua_register(L,"objetMethod",ObjetLuaInterface::luaCall_method);

  lua_sethook(L, &LineHookFunc, LUA_MASKCOUNT, 15);
  int ret = luaL_dofile(L, "script.lua");

  if(ret != 0){
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
  }

  ret = luaL_dofile(L, "script.lua");

  if(ret != 0){
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
  }

  ret = luaL_dofile(L, "script.lua");

  if(ret != 0){
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
  }

  obj.print();
  // while (fgets(buff, sizeof(buff), stdin) != NULL) {
  //   error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
  //           lua_pcall(L, 0, 0, 0);
  //   if (error) {
  //     fprintf(stderr, "%s", lua_tostring(L, -1));
  //     lua_pop(L, 1);  /* pop error message from the stack */
  //   }
  // }

  for ( int i = 0; i < 10; i++)
  {
    call_laFonction(L);
  }

  lua_close(L);
  return 0;
}

