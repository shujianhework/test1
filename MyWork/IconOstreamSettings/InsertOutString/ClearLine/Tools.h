#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include "Int.h"
#include "Double.h"
#include "Boolean.h"
class Tools
{
private:
	static std::map<std::string, std::string> cmds;
	static std::string DefLanguage;
	static std::map<std::string, std::string> shortIni;
	static std::map<std::string, std::string> longIni;
public:
	Tools();
	virtual ~Tools();
	static bool insertHelps(std::string key, std::string shortstr = "", std::string longstr = "");
	static std::string showHelps();
	static bool initCmds(int argc, _TCHAR* argv[]);
	static bool getCmds(std::string key, Int &value);
	static bool getCmds(std::string key, Double &value);
	static bool getCmds(std::string key, Boolean &value);
	static bool getCmds(std::string key, std::string &value);
	static std::string LanguageByKey(std::string keyName,std::string language = "");
	inline static bool getCmdByName(std::string name, bool& t){
		return true;
	}
	inline static bool getCmdByNameStr(std::string name, std::string &ret){
		if (cmds.find(name) != cmds.end())
		{
			ret = cmds[name];
			return true;
		}
		return false;
	}
	inline static bool getCmdByNameStr(std::string name, bool &ret){
		if (cmds.find(name) != cmds.end())
		{
			std::string var = cmds[name];
			if (var == "0" || var == "False" || var == "false" || var == "ผู" || var == "0.0")
				ret = false;
			else
				ret = true;
			return true;
		}
		return false;
	}
	inline static bool getCmdByNameStr(std::string name, long long &ret){
		if (cmds.find(name) != cmds.end())
		{
			std::string var = cmds[name];
			if (var == "")
				return false;
			
		}
		return true;
	}
};

