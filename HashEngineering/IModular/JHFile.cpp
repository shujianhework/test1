#include "JHFile.h"
JHFile::JHFile(std::string path):data(NULL),datalen(0){
	FILE *f = NULL;
	fopen_s(&f, path.c_str(), "rb");
	if (f == NULL)
	{
		return;
	}
	fseek(f, 0, SEEK_END);
	datalen = (long)ftell(f);
	if (datalen > 0){
		data = new unsigned char[datalen + 5];
		memset(data, 0, datalen + 5);
		fseek(f, 0, SEEK_SET);
		fread_s(data, datalen + 5, sizeof(unsigned char), datalen, f);
	}
	fclose(f);
	f = NULL;
}
JHFile::~JHFile()
{
	if (data != NULL)
		delete data;
	data = NULL;
	datalen = 0;
}
