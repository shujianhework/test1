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
	ParamProcHandler__RunLibSysFun(str, autograph, proc);
	FreeLibrary(lib);
	return false;
}
#undef RETURN