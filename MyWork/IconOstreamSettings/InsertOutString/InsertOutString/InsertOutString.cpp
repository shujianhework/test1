// InsertOutString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Tools.h"
//测试空工程
int _tmain(int argc, _TCHAR* argv[])
{
	Tools::insertHelps("type", "类型", "具体类型");
	Tools::insertHelps("testC", "类型C", "具体类型C");
	Tools::insertHelps("testA", "类型A", "具体类型A");
	Tools::insertHelps("testB", "类型B", "具体类型B");
	Tools::insertHelps("testD", "类型D", "具体类型D");
	Tools::insertHelps("testE", "类型E", "具体类型E");
	Tools::insertHelps("help", "帮助");
	if (Tools::initCmds(argc, argv)){
		std::string str1 = "";
		if (Tools::getCmds("help", str1)){
			std::cout << "帮助,合法参数列表" << std::endl;
			std::string str = Tools::showHelps();
			std::cout << argv[0] << std::endl;
			std::cout << str << std::endl;
			return 0;
		}
	}
	else{
		std::string str = Tools::showHelps();
		std::cout << "命令行错误,合法参数列表" << std::endl;
		std::cout << argv[0] << std::endl;
		std::cout << str << std::endl;
		return -1;
	}
	return 0;
}

