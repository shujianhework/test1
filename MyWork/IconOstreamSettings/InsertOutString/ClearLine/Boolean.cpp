#include "stdafx.h"
#include "Boolean.h"
Boolean::~Boolean()
{
}
#include <string>
Boolean Boolean::parse(const char *p, int len){
	if (p == NULL)
		return false;
	if (len == 0)
		len = strlen(p);
	std::string strp = std::string(p, len);
	if (strp == "0" || strp == "0.0" || strp == "false" || strp == "False" || strp == "FALSE" || strp == "ผู"){
		return false;
	}
	return true;
}