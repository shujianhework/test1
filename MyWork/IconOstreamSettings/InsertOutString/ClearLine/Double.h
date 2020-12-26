#pragma once
#include "Int.h"
#include <iostream>
#include <iomanip>
class Double
{
	double var;
	const static double minimumNumberInterval;
	static Int integerVal;
	static Int decimalVal;
public:
	static Double parse(const char *p, int len = 0);
	inline static Double parse(std::string str){
		const char *p = str.c_str();
		return parse(p, str.size());
	}
	static double dotDecimalVal(const char *p,int len = 0,int base = 10);
	Double(double val) :var(val){}
	Double(float val) :var(val){}
	Double operator+(const Double& a){
		return (var + a.var);
	}
	Double operator-(const Double& a){
		return (var - a.var);
	}
	Double operator*(const Double& a){
		return (var * a.var);
	}
	Double operator/(const Double& a){
		return (var / a.var);
	}
	bool operator!=(const Double& a){
		return !(*this == a);
	}
	bool operator<(const Double& a){
		return var < a.var;
	}
	bool operator>(const Double& a){
		return var > a.var;
	}
	bool operator==(const Double& a){
		if ((var + minimumNumberInterval) > a.var && (var - minimumNumberInterval) < a.var)
			return true;
		return false;
	}
	bool operator<=(const Double& a){
		return var <= a.var;
	}
	bool operator>=(const Double& a){
		return var >= a.var;
	}
	bool operator||(const Double& a){
		return a.var || var;
	}
	bool operator&&(const Double& a){
		return a.var && var;
	}
	bool operator!(){
		return var == 0;
	}
	void operator++(){
		var++;
	}
	void operator--(){
		var--;
	}

	void operator+(){
		var = var;
	}
	void operator-(){
		var = 0 - var;
	}
	double operator*(){
		return var;
	}
	void operator = (const Double& a){
		var = a.var;
	}
	void operator+=(const Double &a){
		var += a.var;
	}
	void operator-=(const Double &a){
		var -= a.var;
	}
	void operator*=(const Double &a){
		var *= a.var;
	}
	void operator/=(const Double &a){
		var /= a.var;
	}
	void operator<<=(const Double &a){
		var += a.var;
	}
	void operator>>=(const Double &a){
		var -= a.var;
	}
	friend std::ostream& operator<<(std::ostream &os, Double a){
		static char arr[100] = "";
		sprintf_s(arr, "%25.16f", a.var);
		int len = strlen(arr);
		for (int  i = len-1; i >=0; i--)
		{
			char c = arr[i];
			if (c == '.'){
				arr[i] = 0;
				break;
			}
			else if (c != '0'){
				arr[i + 1] = 0;
				break;
			}

		}
		os << arr;
		return os;
	}
	friend std::istream& operator>>(std::istream &is, Double a){
		is >> a.var;
		return is;
	}
};