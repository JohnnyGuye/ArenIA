#include <stdio.h>
#include <iostream>
#include <string>
#include "objet.h"
#include "LuaHandler.h"

using namespace std;

// Hook lua qui permet de "compter" le
// nombre d'opérations effectuées par le script
// lua et d'arreter le programme si il prends trop
// de temps à s'executer


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



void call_laFonction(lua_State *L)
{
  // 
  lua_getglobal(L, "laFonction");
  lua_pcall(L,0,0,0);
}


int main (void) {
  LuaHandler handler;

  handler.LoadFile("script.lua");
  handler.Execute();
  handler.Execute();
  handler.Execute();
  handler.Execute();
  handler.Execute();
  
  return 0;
}