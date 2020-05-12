#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
class JHFile
{
protected:
	unsigned char *data;
	long datalen;
public:
	JHFile(std::string path);
	void show(){
		if (data){
			std::cout << data << std::endl;
		}
	}
	virtual ~JHFile();
};

