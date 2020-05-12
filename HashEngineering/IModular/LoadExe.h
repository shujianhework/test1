#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
class LoadExe
{
	std::string file;
	void NTHandle(IMAGE_NT_HEADERS *nt);
	void DOSHandle(_IMAGE_DOS_HEADER *dos);
	void FILEHandle(IMAGE_FILE_HEADER *ifile);
	void OPTIONALHandle(IMAGE_OPTIONAL_HEADER *rom);
	char *filedata;
public:
	LoadExe(std::string path);
	~LoadExe();
	void run();
	void test();
};

