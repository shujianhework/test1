#pragma once
#include "HelpInfo.h"
#include "ListArgs.h"
#define GETPARAMHEAD(str)  ListArgs la(str);
#define GETPARAMSIZE  la.len()

#define Int(idx) la.getInt(idx)
#define UInt(idx) la.getUInt(idx)
#define Double(idx) la.getdouble(idx)
#define Float(idx) la.getfloat(idx)
#define String(idx) la.getstring(idx)
#define Boolean(idx) la.getbool(idx)

typedef bool(*ParamProcFunc)(std::map<std::string, std::string>);
class ParamProcHandler
{
public:
	static bool RunLibSysFun(std::map<std::string, std::string> param);
	static bool Sleep(std::map<std::string, std::string> param);
	static bool CocosResCompile(std::map<std::string, std::string> param);
	static bool CheckLangaugeCode(std::map<std::string, std::string> param);
	static bool Mp3(std::map<std::string, std::string> param);
	static bool binExportFuns(std::map<std::string, std::string> param);
	static void push(std::string key, std::string helpinfo, ParamProcFunc func);
	static void Run(std::map<std::string, std::string>& param);	
	static void Md5(std::map<std::string, std::string> &param);
};