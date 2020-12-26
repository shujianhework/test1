// IModular.cpp : �������̨Ӧ�ó������ڵ㡣
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
			throw std::exception("ȱ��type����");
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

	std::string str = "-lib \"lib����·����ϵͳ��·��\" -fun \"������\" -autograph ����ǩ��";
	str = str + "(i[int],I[unsigned int],l[long],L[unsigned long],d[double],f[float],s[std::string],b[bool],v[void]) ��֧��ָ�����õ�vֻ�����ڷ���ֵ����";
	ParamProcHandler::push("RunLibSysFun", str, ParamProcHandler::RunLibSysFun);
	ParamProcHandler::push("Sleep", "-param [\"ʱ�䳤��(int)\"]", ParamProcHandler::Sleep);
	ParamProcHandler::push("binExportFuns", "-infile [\"��Ҫ�������ļ�(exe dll lib)\"]", ParamProcHandler::binExportFuns);
	
}