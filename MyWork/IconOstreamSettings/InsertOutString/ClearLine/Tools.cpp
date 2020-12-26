#include "stdafx.h"
#include "Tools.h"
#include <Windows.h>
#include <vector>
#include <algorithm>
#ifndef CCLOG
#define CCLOG printf
#endif
std::map<std::string, std::string> Tools::cmds = {};
std::map<std::string, std::string> Tools::longIni = {};
std::map<std::string, std::string> Tools::shortIni = {};
std::string Tools::DefLanguage = "en";
Tools::Tools()
{
}
Tools::~Tools()
{
}

static std::wstring StringUtf8ToWideChar(const std::string& strWideChar){
	std::wstring ret;
	if (!strWideChar.empty())
	{
		int nNum = MultiByteToWideChar(CP_UTF8, 0, strWideChar.c_str(), -1, nullptr, 0);
		if (nNum)
		{
			wchar_t* utf8String = new wchar_t[nNum + 1];
			utf8String[0] = 0;

			nNum = MultiByteToWideChar(CP_UTF8, 0, strWideChar.c_str(), -1, utf8String, nNum + 1);

			ret = utf8String;
			delete[] utf8String;
		}
		else
		{
			CCLOG("Wrong convert to Utf8 code:0x%x", GetLastError());
		}
	}

	return ret;
}
static std::string StringWideCharToUtf8(const std::wstring& strWideChar)
{
	std::string ret;
	if (!strWideChar.empty())
	{
		int nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
		if (nNum)
		{
			char* utf8String = new char[nNum + 1];
			utf8String[0] = 0;

			nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, utf8String, nNum + 1, nullptr, FALSE);

			ret = utf8String;
			delete[] utf8String;
		}
		else
		{
			CCLOG("Wrong convert to Utf8 code:0x%x", GetLastError());
		}
	}

	return ret;
}
bool Tools::initCmds(int argc1, _TCHAR* argv[]){
	if (cmds.size() > 0){
		return false;
	}
	size_t argc = argc1;
	if (shortIni.size() != longIni.size() || !shortIni.size())
		return false;
	if (argc % 2 == 0)
		return false;
	std::map<std::string, std::string> temp = {};
	for (size_t i = 1; i < argc; i+=2)
	{
		std::string tkey = "";// argv[i];
		std::string tvalue = "";// argv[i + 1];
#ifdef _UNICODE
		//tkey = WideCharToMultiByte()
		std::wstring temp1 = argv[i];
		tkey = StringWideCharToUtf8(temp1);
		
		std::wstring temp3 = argv[i+1];
		tvalue = StringWideCharToUtf8(temp3);
#else
		tkey = argv[i];
		tvalue = argv[i + 1];
#endif
		if (tkey.c_str()[0] == '-')
			tkey = tkey.substr(1, tkey.length());
		transform(tkey.begin(), tkey.end(), tkey.begin(), tolower);
		temp.insert(std::make_pair(tkey, tvalue));
	}
	for each (auto var in temp)
	{
		auto tempdata = shortIni.find(var.first);
		if (tempdata == shortIni.end()){
			tempdata = shortIni.find("-" + var.first);
			if (tempdata == shortIni.end()){
				tempdata = longIni.find(var.first);
				if (tempdata == longIni.end()){
					tempdata = longIni.find("-"+var.first);
					if (tempdata == longIni.end()){
						printf("%s:%s",LanguageByKey("Command_Line_Param_Not_Find_Define").c_str(), var.first);
						return false;
					}
				}
			}
		}
	}
	cmds = temp;
	return true;
}
//暂时用map 后边用db 最后用语言包 和 软件安装插入方式。
std::string Tools::LanguageByKey(std::string keyName, std::string language){
	if (keyName == "")
		return "";
	static std::map<std::string, std::map<std::string, std::string>> languagedbs = {};
	static std::map<std::string, std::string> temp01 = {};
	if (languagedbs.size() == 0){
		std::map<std::string, std::string> datas = {};
		datas.insert(std::make_pair("error","error"));
		datas.insert(std::make_pair("Command_Line_Param_Not_Find_Define", "Command Line Param Not Find Define"));
		//datas.insert(std::make_pair("Command_Line_Param_Not_Find_Define", "Command Line Param Not Find Define"));
		languagedbs.insert(std::make_pair("en",datas));
	}
	if (language != ""){
		if (languagedbs.find(language) != languagedbs.end())
			language = DefLanguage;
	}
	else{
		language = DefLanguage;
	}
	auto var = languagedbs.find(language)->second.find(keyName);
	if (var == temp01.end())
		return "";
	return var->second;
}
bool Tools::getCmds(std::string key, Int &value){
	value = 0;
	try{
		auto iter = cmds.find(key);
		if (iter == cmds.end())
			return false;
		value = Int::parse(iter->second.c_str());
		return true;
	}
	catch (TypeException ){
		return false;
	}
	catch (TypeException *){
		return false;
	}
}
bool Tools::getCmds(std::string key, Double &value){
	value = 0.0;
	try{
		auto iter = cmds.find(key);
		if (iter == cmds.end())
			return false;
		value = Double::parse(iter->second.c_str());
		return true;
	}
	catch (TypeException ){
		return false;
	}
	catch (TypeException *){
		return false;
	}
}
bool Tools::getCmds(std::string key, Boolean &value){
	value = false;
	auto iter = cmds.find(key);
	if (iter == cmds.end())
		return false;
	value = Boolean::parse(iter->second.c_str());
	return true;
}
bool Tools::getCmds(std::string key, std::string &value){
	value = "";
	auto iter = cmds.find(key);
	if (iter == cmds.end())
		return false;
	value = iter->second.c_str();
	return true;
}
bool Tools::insertHelps(std::string key, std::string shortstr, std::string longstr){
	if (key == "")
		return false;
	transform(key.begin(), key.end(), key.begin(), tolower);
	longIni.insert(std::make_pair(key, longstr));
	shortIni.insert(std::make_pair(key, shortstr));
	return true;
}
std::string Tools::showHelps(){
	std::string ret = "";
	for each (auto var in shortIni)
	{
		std::string temp = "\t";
		temp = temp + var.first + ":" + var.second + "(" + longIni[var.first] + ")";
		ret = ret + temp + "\n";
	}
	return ret;
}