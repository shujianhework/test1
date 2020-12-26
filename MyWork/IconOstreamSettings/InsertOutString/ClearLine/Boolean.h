#pragma once
#include <iostream>
class Boolean
{
public:
	bool mValue;
	Boolean(bool value = false) :mValue(value){}
	~Boolean();
	static Boolean parse(const char *p = NULL, int len = 0);
	bool operator!=(const Boolean& a){
		return mValue != a.mValue;
	}
	
	bool operator==(const Boolean& a){
		return mValue == a.mValue;
	}
	bool operator||(const Boolean& a){
		return mValue || a.mValue;
	}

	bool operator&&(const Boolean& a){
		return mValue && a.mValue;
	}

	bool operator!(){
		return !mValue;
	}
	bool operator*(){
		return mValue;
	}
	Boolean operator^(const Boolean&a){
		return mValue ^ a.mValue;
	}
	
	void operator = (const Boolean& a){
		mValue = a.mValue;
	}
	friend std::ostream& operator<<(std::ostream &os, Boolean a){
		os << a.mValue ? "true" :  "false";
		return os;
	}
};