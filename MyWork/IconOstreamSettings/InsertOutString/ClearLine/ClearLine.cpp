// ClearLine.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Types.h"
#include "Tools.h"
#include "App.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Tools::insertHelps("type", "����", "��������");
	Tools::insertHelps("in", "�����ļ�","ȫ·��");
	Tools::insertHelps("out", "����ļ�", "ȫ·��������,in:sub(1,0-strlen(exname))+.type");
	/*Tools::insertHelps("testB", "����B", "��������B");
	Tools::insertHelps("testD", "����D", "��������D");
	Tools::insertHelps("testE", "����E", "��������E");*/
	Tools::insertHelps("help", "����");
	if (Tools::initCmds(argc, argv)){
		std::string str1 = "";
		if (Tools::getCmds("help", str1)){
			std::cout << "����,�Ϸ������б�" << std::endl;
			std::string str = Tools::showHelps();
			std::cout << argv[0] << std::endl;
			std::cout << str << std::endl;
			return 0;
		}
		else{
		}
	}
	else{
		std::string str = Tools::showHelps();
		std::cout << "�����д���,�Ϸ������б�" << std::endl;
		std::cout << argv[0] << std::endl;
		std::cout << str << std::endl;
		return -1;
	}
	return 0;
	return 0;
}

