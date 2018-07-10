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

	void Init();            //��ʼ��Lua����ָ�����  
	void Close();         //�ر�Lua����ָ��  

	bool LoadLuaFile(const char* pFileName);                              //����ָ����Lua�ļ�  
	bool CallFileFn(const char* pFunctionName, int nParam1, int nParam2);        //ִ��ָ��Lua�ļ��еĺ���  
	bool CallFileFn(const char* pFunctionName, CParamGroup& ParamIn, CParamGroup& ParamOut);

	void test() const;

	bool InitClass();

private:
	bool PushLuaData(lua_State* pState, _ParamData* pParam);
	bool PopLuaData(lua_State* pState, _ParamData* pParam, int nIndex);

private:  
	lua_State* m_pState;   //�����Lua��State����ָ�룬�����һ��lua�ļ���Ӧһ����  
};

#endif // _LUA_FN_H_