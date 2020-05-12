#include "HelpInfo.h"
std::map<std::string,std::string> HelpInfo::HelpMap = {};
std::string HelpInfo::type = "";
void HelpInfo::init(){
	type = "";
	HelpMap.clear();
}
void HelpInfo::push(std::string key, std::string help)throw(std::exception){
	if (HelpMap.find(key) != HelpMap.end()){
		throw std::exception("ÖØ¸´µÄkeyÖµ");
	}
	HelpMap[key] = help;
	return;
}
void HelpInfo::settype(std::string Type){
	if (HelpMap.find(Type) != HelpMap.end())
		type = Type;
}
void HelpInfo::showerror(std::string what){
	std::string str = "";
	std::string modulename = ClassTools::GetModuleName();
	if (type == ""){
		for (auto iter = HelpMap.begin(); iter != HelpMap.end(); iter++){
			str = str + modulename + "\t\t -Type " + iter->first + " " + iter->second + "\n";
		}
	}
	else
		str = modulename + "\t\t -Type " + type + " " + HelpMap[type];
	if (what.length() > 0){
		std::cout << "error infos  " << what << std::endl;
	}
	std::cout << str << std::endl;
}