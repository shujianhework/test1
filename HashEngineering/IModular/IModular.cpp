// IModular.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "HelpInfo.h"
#include "ParamProcHandler.h"
#include "Mp3.h"
#include <Windows.h>
#include <DbgHelp.h>
#include "LoadExe.h"
#pragma comment(lib,"Dbghelp.lib")
void pushhelps();

void test0(){
	Mp3 jf = "V:/LeisureTime/Music/����/���� - �����ɳ.mp3";
	jf.init();
	//jf.show();
}
_declspec(dllexport) int testfun(){
	return 0;
}
int test(){
	char arr[256] = "";
	std::string str = "?CopyInfo@CTest@@IAEXABV1@@Z";
	std::cout << str << std::endl;
	UnDecorateSymbolName(str.c_str(), arr, 255, 0);
	
	std::cout << arr << std::endl;
	return 0;
}
template<typename Ret,typename F>
bool testf(Ret& t1,F f){
	t1 = f();
	return true;
}
int _tmain(int argc, _TCHAR* argv[])
{
	try{
		/*HelpInfo::init();
		pushhelps();
		std::map<std::string, std::string> data = ClassTools::HeadTrance(argc, argv);
		if (data.find("TYPE") != data.end()){
			HelpInfo::settype(data["TYPE"]);
			ParamProcHandler::Run(data);
		}
		else
			throw std::exception("ȱ��type����");*/
		//test();
		/*int ret = 5;
		testf<int,decltype(test)>(ret,test);
		std::cout << ret << std::endl;*/
		LoadExe p("../Debug/IModular.exe");// ("F:\\Tools\\vs\\Tools\\Release\\TestDll.dll");
		p.run();
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
	ParamProcHandler::push("Md5s", "-in src -model [1 md5(src) 2 md5(open(src)] 3 table = open(src) for md5(open(v)) ");
}