#include "stdafx.h"
#include "App.h"

std::map<std::string, AppStaticFun*> App::funcs = {};
App::App()
{
}


App::~App()
{
}
bool App::init(){
	funcs.insert(std::make_pair("Pretreatment", Pretreatment));
	return true;
}
bool App::run(std::string key, void *data, int len, std::function<void(void *p, int len)> back, bool isfile){
	auto iter = funcs.find(key);
	if (iter == funcs.end())
		return false;
	return iter->second(data, len, back, isfile);
}