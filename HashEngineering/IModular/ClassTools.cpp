#include "ClassTools.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <Windows.h>
std::map<std::string, std::string> ClassTools::HeadTrance(int argc, char*argv[]) throw(std::exception){
	std::map<std::string, std::string> ret = {};
	std::string key = "";
	int len = 0;
	for (int i = 1; i < argc; i++)
	{
		if (i % 2 == 1){
			len = strlen(argv[i]);
			if (len < 2){
				throw new std::exception("命令行参数 Key值错误");
			}
			key = argv[i];
			key = key.substr(1, key.length() - 1);
			TranceString(key, false);
		}
		else{
			ret.insert(std::make_pair(key, argv[i]));
		}
	}
	if (ret.find("TYPE") == ret.end()){
		throw std::exception("");
	}
	return ret;
}
void ClassTools::TranceString(std::string &str, bool Big2Small){
	if (Big2Small)
		transform(str.begin(), str.end(), str.begin(), ::tolower);
	else
		transform(str.begin(), str.end(), str.begin(), ::toupper);
}
std::string ClassTools::GetModuleName(){
	char szFileFullPath[MAX_PATH];// , szProcessName[MAX_PATH];
	::GetModuleFileNameA(NULL, szFileFullPath, MAX_PATH);
	std::string FileFullPath = szFileFullPath;
	return FileFullPath;
}