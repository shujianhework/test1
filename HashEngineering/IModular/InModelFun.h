#ifndef IModular__Test001__InModelFun
#define IModular__Test001__InModelFun
#include <iostream>
#include <Windows.h>
#include "ParamProcHandler.h"
typedef int(__stdcall *NPROC)();
#define SWITCH(nstr) {std::string tempstr = nstr;bool isbreak = false;
#define SWITCHEND }
#define CASE(str) if(isbreak == false && str == tempstr){
#define BREAK	isbreak = true;}
#define DEFAULT if(isbreak == false){
#define RETURN  return true
#define PARAMLIST(...) auto p = (void(*)(##__VA_ARGS__))proc
#define CALLPARAMPROC(...) p(##__VA_ARGS__)
#define ERROROUT(str) std::exception(str)
#define LOCALFUN(str,model,...) CASE("v,"str) decltype(model)* p = (decltype(model)*)proc;p(##__VA_ARGS__);RETURN;}
#define MAKEFUN(Name,...) void __stdcall automake##Name(##__VA_ARGS__){}
//bool ParamProcHandler__RunLibSysFun(std::string str, std::string autograph, NPROC  proc);
#endif