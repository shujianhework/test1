// IModular.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HelpInfo.h"
#include "ParamProcHandler.h"
#include "Mp3.h"
#include <Windows.h>
#include <DbgHelp.h>
#include "LoadExe.h"
#pragma warning(disable:4305 4309)
#pragma comment(lib,"ole32")
#pragma comment(lib,"comsupp")
#include <objbase.h>
#include <comip.h>
#include <mlang.h>
void pushhelps();

int achar2wchar(char *p, int len, wchar_t *&wc){
	if (wc != NULL)
		delete wc;
	wc = NULL;
	int wlen = MultiByteToWideChar(CP_ACP, 0, p, len, NULL, 0);
	if (wlen > 0){
		wc = new wchar_t[wlen+1];
		wc[wlen] = 0;
		MultiByteToWideChar(CP_ACP, 0, p, len, wc, wlen);
	}
	return wlen;
}
int _tmain(int argc, _TCHAR* argv[])
{
	try{
		HelpInfo::init();
		pushhelps();
		std::map<std::string, std::string> data = ClassTools::HeadTrance(argc, argv);
		if (data.find("TYPE") != data.end()){
			HelpInfo::settype(data["TYPE"]);
			ParamProcHandler::Run(data);
		}
		else
			throw std::exception("缺少type类型");
		//LoadExe p("../Debug/IModular.exe");// ("F:\\Tools\\vs\\Tools\\Release\\TestDll.dll");
		//p.run();
		
	}
	catch (std::exception ex){
		HelpInfo::showerror(ex.what());
		exit(-1);
	}
	return 0;
}
void pushhelps(){

	std::string str = "-lib \"lib绝对路径或系统库路径\" -fun \"函数名\" -autograph 函数签名";
	str = str + "(i[int],I[unsigned int],l[long],L[unsigned long],d[double],f[float],s[std::string],b[bool],v[void]) 不支持指针引用等v只能用在返回值上面";
	ParamProcHandler::push("RunLibSysFun", str, ParamProcHandler::RunLibSysFun);
	ParamProcHandler::push("Sleep", "-param [\"时间长度(int)\"]", ParamProcHandler::Sleep);
	ParamProcHandler::push("binExportFuns", "-infile [\"需要解析的文件(exe dll lib)\"]", ParamProcHandler::binExportFuns);
	
}