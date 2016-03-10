#ifndef _FUNCTION_WRAPPER_H_
#define _FUNCTION_WRAPPER_H_

class FunctionWrapper 
{
public:
	virtual void luaCall(lua_State *L) = 0;
};

#endif