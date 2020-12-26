#include "stdafx.h"
#include "Double.h"
const double Double::minimumNumberInterval = 0.000000000000000001;
Int Double::decimalVal = 0;
Int Double::integerVal = 0;
double Double::dotDecimalVal(const char *p, int len,int base)
{
	//double bases[20] = { 0 };
	double ret = 0;
	long long lbase = 1;
	for (int i = 0; i < len; i++)
	{
		char c = p[i];
		char bit = 255;
		if (c >= '0' && c < '8'){
			bit = c - '0';
		}
		else if (base > 8 && (c == '8' || c == '9')){
			bit = c - '0';
		}
		else if (base == 16 && (c >= 'a' && c <= 'e')){
			bit = 10 + c - 'a';
		}
		else if (base == 16 && (c >= 'A' && c <= 'E')){
			bit = 10 + c - 'A';
		}
		if (bit == 255){
			char arr[100] = "";
			sprintf_s(arr, "Double.parse() decimalValue Param error char %c in base = %d", c, base);
		}
		lbase = lbase * base;
		ret = ret +  bit / (double)lbase;
	}
	return ret;
}
Double Double::parse(const char *p, int len ){
	if (len == 0)
		len = strlen(p);
	if (len > 100){
		throw TypeException("Double char buff len overflow");
	}
	int dot = -1;
	for (int i = 0; i < len; i++)
	{
		char c = p[i];
		if (c == '.'){
			if (dot < 0)
				dot = i;
			else
				throw TypeException("Double Muilt Dot Operator ");
		}
	}
	Double value = 0.0f;
	if (dot == -1){
		integerVal = Int::parse(p,len);
		value = (double)*integerVal;
		return value;
	}
	else{
		char arr[100] = "";
		memcpy(arr, p, dot);
		arr[dot] = 0;
		integerVal = Int::parse(arr);
		std::string strarr = arr;
		int System = 0;
		if (strarr.find('x') != std::string::npos || strarr.find('X') != std::string::npos){
			System = 16;
		}
		else if(arr[0] == '0' || (arr[0] == '-' && arr[1] == '0') ){//0Лђеп 8
			System = integerVal == 0 ? 10:8;
		}
		else
		{
			System = 10;
		}
		double dec = Double::dotDecimalVal(&p[dot + 1], strlen(&p[dot + 1]), System);
		if (integerVal < 0){
			dec = 0 - dec;
		}
		double data = *integerVal;
		data = data + dec;
		Double ret = data;
		return ret;
	}
}