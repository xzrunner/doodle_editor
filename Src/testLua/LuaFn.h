#ifndef _LUA_FN_H_
#define _LUA_FN_H_

extern "C"   
{  
#include "lua.h"  
#include "lualib.h"  
#include "lauxlib.h"
#include "tolua++.h"
};  

class CParamGroup;
struct _ParamData;

class CLuaFn  
{  
public:  
	CLuaFn(void);  
	~CLuaFn(void);  

	void Init();            //初始化Lua对象指针参数  
	void Close();         //关闭Lua对象指针  

	bool LoadLuaFile(const char* pFileName);                              //加载指定的Lua文件  
	bool CallFileFn(const char* pFunctionName, int nParam1, int nParam2);        //执行指定Lua文件中的函数  
	bool CallFileFn(const char* pFunctionName, CParamGroup& ParamIn, CParamGroup& ParamOut);

	void test() const;

	bool InitClass();

private:
	bool PushLuaData(lua_State* pState, _ParamData* pParam);
	bool PopLuaData(lua_State* pState, _ParamData* pParam, int nIndex);

private:  
	lua_State* m_pState;   //这个是Lua的State对象指针，你可以一个lua文件对应一个。  
};

#endif // _LUA_FN_H_