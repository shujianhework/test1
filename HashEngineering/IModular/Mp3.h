#pragma once
#include "JHFile.h"
#include <map>
struct ID3V2{
	char Header[3];
	char Ver;
	char Revision;
	char Flag;
	char Size[4];
};
struct ID3V2Frame{
	char Frame[4];
	char Size[4];
	char Flages[2];
};
class Mp3 :public JHFile
{
	ID3V2 *id3v2;
	std::map<int, std::string> FrameInfos;
public:
	Mp3(std::string path);
	void init();
	~Mp3();
};

