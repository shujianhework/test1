#pragma once
#pragma warning (disable:4290)
#include <map>
#include <iostream>
#include <string>
#include "ClassTools.h"
class HelpInfo{
private:
	static std::map<std::string, std::string> HelpMap;
	static std::string type;
public:
	static void init();
	static void push(std::string key, std::string help)throw(std::exception);
	static void settype(std::string Type);
	static void showerror(std::string what);
};