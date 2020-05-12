#pragma once
#include <iostream>
#include <string>
#include <vector>
class ListArgs
{
	std::vector<std::string> argv;
public:
	ListArgs(std::string param);
	int getInt(unsigned int idx);
	unsigned int getUInt(unsigned int idx);
	double getdouble(unsigned int idx);
	float getfloat(unsigned int idx);
	std::string getstring(unsigned int idx);
	bool getbool(unsigned int idx);
	inline int len(){
		return argv.size();
	}
	~ListArgs();
};

