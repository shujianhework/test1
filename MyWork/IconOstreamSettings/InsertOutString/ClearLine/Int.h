#pragma once
#include "Types.h"
class Int
{
	long long var;
public:
	static Int parse(const char *p, int len =0);
	Int(long long val) :var(val){}
	//10进制下这个多少位
	static inline int PostionLenBy10(Int& val){
		long long llval = *val;
		if (llval < 0)
			llval = 0 - llval;
		int bit = 0;
		while (llval > 9){
			bit++;
			llval = llval / 10;
		}
		bit++;
		return bit;
	}
	Int operator+(const Int& a){
		return (var + a.var);
	}
	Int operator-(const Int& a){
		return (var - a.var);
	}
	Int operator*(const Int& a){
		return (var * a.var);
	}
	Int operator/(const Int& a){
		return (var / a.var);
	}
	Int operator%(const Int& a){
		return (var % a.var);
	}

	bool operator!=(const Int& a){
		return a.var != var;
	}
	bool operator<(const Int& a){
		return var < a.var;
	}
	bool operator>(const Int& a){
		return var > a.var;
	}
	bool operator==(const Int& a){
		return a.var == var;
	}
	bool operator<=(const Int& a){
		return var <= a.var;
	}
	bool operator>=(const Int& a){
		return var >= a.var;
	}


	bool operator||(const Int& a){
		return a.var || var;
	}

	bool operator&&(const Int& a){
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
	long long operator*(){
		return var;
	}
	Int operator|(const Int&a){
		return var | a.var;
	}
	Int operator&(const Int&a){
		return var & a.var;
	}
	Int operator~(){
		return ~var;
	}
	Int operator^(const Int&a){
		return var ^ a.var;
	}
	Int operator<<(const Int&a){
		return var << a.var;
	}
	Int operator>>(const Int&a){
		return var >> a.var;
	}

	void operator = (const Int& a){
		var = a.var;
	}
	void operator+=(const Int &a){
		var += a.var;
	}
	void operator-=(const Int &a){
		var -= a.var;
	}
	void operator*=(const Int &a){
		var *= a.var;
	}
	void operator/=(const Int &a){
		var /= a.var;
	}
	void operator%=(const Int &a){
		var %= a.var;
	}
	void operator&=(const Int &a){
		var &= a.var;
	}
	void operator|=(const Int &a){
		var |= a.var;
	}
	void operator^=(const Int &a){
		var ^= a.var;
	}
	void operator<<=(const Int &a){
		var += a.var;
	}
	void operator>>=(const Int &a){
		var -= a.var;
	}
	friend std::ostream& operator<<(std::ostream &os,Int a){
		os << a.var;
		return os;
	}
	friend std::istream& operator>>(std::istream &is, Int a){
		is >> a.var;
		return is;
	}
	~Int(){}
};