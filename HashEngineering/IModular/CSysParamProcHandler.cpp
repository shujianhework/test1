#include "ParamProcHandler.h"
#include "InModelFun.h"
#include <Windows.h>
bool ParamProcHandler::Sleep(std::map<std::string, std::string> param){
	std::string str = param["PARAM"];
	GETPARAMHEAD(str);
	::Sleep(Int(0));
	
	return true;
}
bool ParamProcHandler::Mp3(std::map<std::string, std::string> param)
{
	return false;
}
void ParamProcHandler::Md5(std::map<std::string, std::string> &param){
	int model = 0;
	std::string str = "";
}
#include "LoadExe.h"
bool ParamProcHandler::binExportFuns(std::map<std::string, std::string> param){
	LoadExe le = param["INFILE"];
	le.run();
	return true;
}
bool ParamProcHandler::RunLibSysFun(std::map<std::string, std::string> param){
	std::string autograph = "";
	if (param.find("LIB") == param.end()){
		return false;
	}
	if (param.find("FUN") == param.end() || param["FUN"] == ""){
		return false;
	}
	
	HMODULE lib = LoadLibrary(param["LIB"].c_str());
	if (INVALID_HANDLE_VALUE == lib){
		return false;
	}
	FARPROC proc = GetProcAddress(lib, param["FUN"].c_str());
	if (proc == NULL)
	{
		FreeLibrary(lib);
		return false;
	}
	if (param.find("AUTOGRAPH") != param.end()){
		autograph = param["AUTOGRAPH"];
	}
	if (autograph == "" || autograph == "V" || autograph == "v"){
		auto p = (void(*)())proc;
		p();
		FreeLibrary(lib);
		return true;
	}
	std::string str = param["PARAM"];
	//ParamProcHandler__RunLibSysFun(str, autograph, proc);
	FreeLibrary(lib);
	return false;
}
bool ParamProcHandler::CheckLangaugeCode(std::map<std::string, std::string> param){
	return false;
}
#include <io.h>
#include <iostream>
#include <functional>
using namespace std;
void listFiles(const char * dir,std::function<void()>)
{
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dir, &findData);    // 查找目录中的第一个文件
	if (handle == -1)
	{
		std::cout << "Failed to find first file!\n";
		return;
	}

	do
	{
		if (findData.attrib & _A_SUBDIR
			&& strcmp(findData.name, ".") == 0
			&& strcmp(findData.name, "..") == 0
			)    // 是否是子目录并且不为"."或".."
			cout << findData.name << "\t<dir>\n";
		else
			cout << findData.name << "\t" << findData.size << endl;
	} while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件

	cout << "Done!\n";
	_findclose(handle);    // 关闭搜索句柄
}
bool ParamProcHandler::CocosResCompile(std::map<std::string, std::string> param){
	std::string str = param["PARAM"];
	GETPARAMHEAD(str);
	//::Sleep(Int(0));

	return true;
}
#undef RETURN