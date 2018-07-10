#include "LuaFn.h"
#include "ParamData.h"
#include "Test.h"

int main()
{
	CLuaFn LuaFn;  

	LuaFn.InitClass();

	LuaFn.LoadLuaFile("lua0.lua");

	CParamGroup inParams, outParams;
	int p0 = 11, p1 = 12, ret;
	inParams.Push(new _ParamData(&p0, "int", sizeof(int)));
	inParams.Push(new _ParamData(&p1, "int", sizeof(int)));
	inParams.Push(new _ParamData(new CTest(), "CTest", sizeof(CTest)));
//	outParams.Push(new _ParamData(&ret, "int", sizeof(int)));
//	LuaFn.CallFileFn("func_Add", inParams, outParams);
  
	outParams.Push(new _ParamData(new CTest(), "CTest", sizeof(CTest)));

	LuaFn.CallFileFn("func_class", inParams, outParams);

//	printf("result: %d", ret);
	CTest* pTestRsult = (CTest* )outParams.GetParam(0)->GetParam();  
	pTestRsult->GetData();

	LuaFn.CallFileFn("func_Add", 11, 12);  
//	LuaFn.test();
	getchar();

	return 0;
}