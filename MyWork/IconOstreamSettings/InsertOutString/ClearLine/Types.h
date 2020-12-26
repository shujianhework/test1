#pragma once
#include <string>
#include <exception>
//#ifdef NDEBUG
//#else
class Object{
	int ret;
public:
	void retain(){ ret++; }
	void release(){ ret--;}
};
//class ObjectPool{
//	static ObjectPool *op;
//public:
//	static ObjectPool *getInstance(){	}
//	static void remove()
//};
class TypeException:public Object,std::exception
{
	char* data;
public:
	TypeException();
	~TypeException();
	TypeException(std::string var);
	virtual std::string toString(){
		return data;
	}
private:
};
//#endif