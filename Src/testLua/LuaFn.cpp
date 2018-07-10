#include "LuaFn.h"
#include "ParamData.h"
#include "Test.h"

CLuaFn::CLuaFn(void)
{
	m_pState = NULL;
	Init();
}

CLuaFn::~CLuaFn(void)
{
	Close();
}

void CLuaFn::Init()
{
	if (NULL == m_pState)
	{
		m_pState = lua_open();
		luaL_openlibs(m_pState);
	}
}

void CLuaFn::Close()
{
	if (NULL != m_pState)
	{
		lua_close(m_pState);
		m_pState = NULL;
	}
}

bool CLuaFn::LoadLuaFile(const char* pFileName)
{
	int nRet = 0;  

	if(NULL == m_pState)  
	{  
		printf("[CLuaFn:: LoadLuaFile]m_pState is NULL./n");  
		return false;  
	}

	nRet = luaL_dofile(m_pState, pFileName);
	if(nRet != 0)
	{
		printf("[CLuaFn:: LoadLuaFile]luaL_loadfile(%s) is file(%d)(%s)./n", pFileName, nRet, lua_tostring(m_pState, -1));  
		return false;
	}

	return true;
}

bool CLuaFn::CallFileFn(const char* pFunctionName, int nParam1, int nParam2)
{
	int nRet = 0;  

	if(NULL == m_pState)  
	{  
		printf("[CLuaFn::CallFileFn]m_pState is NULL./n");  
		return false;  
	}

	lua_getglobal(m_pState, pFunctionName);  

	lua_pushnumber(m_pState, nParam1);  
	lua_pushnumber(m_pState, nParam2);  

	int nIn = lua_gettop(m_pState);

	nRet = lua_pcall(m_pState, 2, 1, 0);
	if (nRet != 0)
	{  
		printf("[CLuaFn::CallFileFn]call function(%s) error(%d)./n", pFunctionName, nRet);  
		return false;  
	}

	if (lua_isnumber(m_pState, -1) == 1)  
	{  
		int nSum = lua_tonumber(m_pState, -1);  
		printf("[CLuaFn::CallFileFn]Sum = %d", nSum);  
	}  

	int nOut = lua_gettop(m_pState);

	return true;
}

bool CLuaFn::CallFileFn(const char* pFunctionName, CParamGroup& ParamIn, CParamGroup& ParamOut)  
{  
	int nRet = 0;  

	int i    = 0;  

	if(NULL == m_pState)  
	{  
		printf("[CLuaFn::CallFileFn]m_pState is NULL./n");  
		return false;  
	}  

	lua_getglobal(m_pState, pFunctionName);  

	//加载输入参数  
	for(i = 0; i < ParamIn.GetCount(); i++)  
	{  
		PushLuaData(m_pState, ParamIn.GetParam(i));  
	}  

	nRet = lua_pcall(m_pState, ParamIn.GetCount(), ParamOut.GetCount(), 0);  

	if (nRet != 0)  
	{  
		printf("[CLuaFn::CallFileFn]call function(%s) error(%s)./n", pFunctionName, lua_tostring(m_pState, -1));  
		return false;  
	}  

	//获得输出参数  
	int nPos = 0;  
	for(i = ParamOut.GetCount() - 1; i >= 0; i--)  
	{  
		nPos--;  
		PopLuaData(m_pState, ParamOut.GetParam(i), nPos);  
	}  

//	int nCount = lua_gettop(m_pState);  

	lua_settop(m_pState, -1-ParamOut.GetCount());  

	return true;  
}

void CLuaFn::test() const
{
	lua_pushnumber(m_pState, 11);  
	lua_pushnumber(m_pState, 12);  

	int nIn = lua_gettop(m_pState);

	int nData1 = lua_tonumber(m_pState, 3);
	int nData2 = lua_tonumber(m_pState, -2);

	printf("[Test]nData1  = %d, nData2  = %d", nData1, nData2); 
}

//////////////////////////////////////////////////////////////////////////

static int tolua_new_CTest(lua_State* pState)  
{  
	CTest* pTest = new CTest();  
	tolua_pushusertype(pState, pTest, "CTest");  
	return 1;
}  

static int tolua_delete_CTest(lua_State* pState)  
{  
	CTest* pTest = (CTest* )tolua_tousertype(pState, 1, 0);  
	if(NULL != pTest)  
	{  
		delete pTest;  
	}  
	return 1;  
}  

static int tolua_SetData_CTest(lua_State* pState)  
{  
	CTest* pTest = (CTest* )tolua_tousertype(pState, 1, 0);  

	const char* pData = tolua_tostring(pState, 2, 0);  

	if(pData != NULL && pTest != NULL)  
	{  
		pTest->SetData(pData);  
	}  

	return 1;  
}  

static int tolua_GetData_CTest(lua_State* pState)  
{  
	CTest* pTest = (CTest* )tolua_tousertype(pState, 1, 0);  

	if(pTest != NULL)  
	{  
		char* pData = pTest->GetData();  
		tolua_pushstring(pState, pData);  
	}  

	return 1;  
} 

//////////////////////////////////////////////////////////////////////////

bool CLuaFn::InitClass()  
{  
	if(NULL == m_pState)  
	{  
		printf("[CLuaFn::InitClass]m_pState is NULL./n");  
		return false;  
	}  

	tolua_open(m_pState);  
	tolua_module(m_pState, NULL, 0);  
	tolua_beginmodule(m_pState, NULL);  

		tolua_usertype(m_pState, "CTest");  
		tolua_cclass(m_pState, "CTest", "CTest", "", tolua_delete_CTest);  

		tolua_beginmodule(m_pState, "CTest");  
			tolua_function(m_pState, "new", tolua_new_CTest);  
			tolua_function(m_pState, "SetData", tolua_SetData_CTest);  
			tolua_function(m_pState, "GetData", tolua_GetData_CTest);  
		tolua_endmodule(m_pState);  

	tolua_endmodule(m_pState);  

	return true;  
} 

bool CLuaFn::PushLuaData(lua_State* pState, _ParamData* pParam)  
{  
	if(pParam == NULL)  
	{  
		return false;  
	}  

	if(pParam->CompareType("string"))  
	{  
		lua_pushstring(m_pState, (char* )pParam->GetParam());  
		return true;  
	}  

	if(pParam->CompareType("int"))  
	{  
		int* nData = (int* )pParam->GetParam();  
		lua_pushnumber(m_pState, *nData);  
		return true;  
	}  
	else  
	{  
		void* pVoid = pParam->GetParam();  
		tolua_pushusertype(m_pState, pVoid, pParam->GetType());  
		return true;  
	}  
}

bool CLuaFn::PopLuaData(lua_State* pState, _ParamData* pParam, int nIndex)  
{  
	if(pParam == NULL)  
	{  
		return false;  
	}  

	if(pParam->CompareType("string"))  
	{  
		if (lua_isstring(m_pState, nIndex) == 1)  
		{  
			const char* pData = (const char*)lua_tostring(m_pState, nIndex);  
			pParam->SetData((void* )pData, (int)strlen(pData));  
		}  
		return true;  
	}  

	if(pParam->CompareType("int"))  
	{  
		if (lua_isnumber(m_pState, nIndex) == 1)  
		{  
			int nData = (int)lua_tonumber(m_pState, nIndex);  
			pParam->SetData(&nData, sizeof(int));  
		}  
		return true;  
	}  
	else  
	{  
		pParam->SetData(tolua_tousertype(m_pState, nIndex, NULL), -1);  
		return true;  
	}  
}