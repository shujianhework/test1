#pragma once
#include <functional>
#include "Tools.h"
typedef bool (AppStaticFun)(void *data, int len, std::function<void(void *p, int len)> back, bool isfile);
class App
{
	static std::map<std::string, AppStaticFun*> funcs;
public:
	App();
	~App();
	static bool init();
	static bool run(std::string key, void *data, int len, std::function<void(void *p, int len)> back,bool isfile = false);
	static bool Pretreatment(void *data,int len, std::function<void(void *p, int len)> back,bool isfile = false);
};

