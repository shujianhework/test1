#include "ParamProcHandler.h"
#include <functional>
#include <iostream>
std::map < std::string, ParamProcFunc > listmap = {};

void ParamProcHandler::push(std::string key, std::string helpinfo, ParamProcFunc func){
	HelpInfo::push(key, helpinfo);

	listmap[key] = func;
}
void ParamProcHandler::Run(std::map<std::string, std::string>& param){
	std::string type = param["TYPE"];
	listmap[type](param);
}
