#pragma once
#pragma warning (disable:4290)
#include <map>
#include <exception>
class ClassTools
{
public:
	static std::map<std::string, std::string> HeadTrance(int argc, char*argv[]) throw(std::exception);
	static void TranceString(std::string &str, bool Big2Small);//
	static std::string GetModuleName();
};

