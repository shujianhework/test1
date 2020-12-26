#include "stdafx.h"
#include "Types.h"
#include <Windows.h>
#ifdef NDEBUG
static const char *getStack(){
}
#else
char *tempbuffs = NULL;
int tempbufflen = 0;
#pragma comment(lib, "Dbghelp.lib")
#include <DbgHelp.h>
static HANDLE g_hHandle;
static HANDLE g_hThread;
static CONTEXT g_context;
void InitTrack(){
	g_hHandle = GetCurrentProcess();
	SymInitialize(g_hHandle, NULL, true);
	if (tempbufflen == 0){
		tempbufflen = 1024;
		tempbuffs = new char[tempbufflen];
		memset(tempbuffs, 0, tempbufflen);
	}
}
void StackTrack(){
	g_hThread = GetCurrentThread();
	STACKFRAME sf = { 0 };

	sf.AddrPC.Offset = g_context.Eip;
	sf.AddrPC.Mode = AddrModeFlat;

	sf.AddrFrame.Offset = g_context.Ebp;
	sf.AddrFrame.Mode = AddrModeFlat;

	sf.AddrStack.Offset = g_context.Esp;
	sf.AddrStack.Mode = AddrModeFlat;

	typedef struct tag_SYMBOL_INFO
	{
		IMAGEHLP_SYMBOL symInfo;
		TCHAR szBuffer[MAX_PATH];
	} SYMBOL_INFO, *LPSYMBOL_INFO;

	DWORD dwDisplament = 0;
	SYMBOL_INFO stack_info = { 0 };
	PIMAGEHLP_SYMBOL pSym = (PIMAGEHLP_SYMBOL)&stack_info;
	pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
	pSym->MaxNameLength = sizeof(SYMBOL_INFO)-offsetof(SYMBOL_INFO, symInfo.Name);
	IMAGEHLP_LINE ImageLine = { 0 };
	ImageLine.SizeOfStruct = sizeof(IMAGEHLP_LINE);
	std::string data = "";
	while (StackWalk(IMAGE_FILE_MACHINE_I386, g_hHandle, g_hThread, &sf, &g_context, NULL, SymFunctionTableAccess, SymGetModuleBase, NULL))
	{
		SymGetSymFromAddr(g_hHandle, sf.AddrPC.Offset, &dwDisplament, pSym);
		SymGetLineFromAddr(g_hHandle, sf.AddrPC.Offset, &dwDisplament, &ImageLine);
		char arr[512] = "";
		sprintf_s(arr,"\t\t: %08x+%s(FILE[%s]LINE[%d])\n", pSym->Address, pSym->Name, ImageLine.FileName, ImageLine.LineNumber);
		data = data + arr;
	}
	if (tempbufflen < (data.size() + 1)){
		delete tempbuffs;
		tempbufflen = data.size() + 10;
		tempbuffs = new char[tempbufflen];
	}
	char *p = (char*)data.c_str();
	memcpy(tempbuffs, p, data.size());
	tempbuffs[data.size()] = 0;
	return;
}
void UninitTrack(){
	SymCleanup(g_hHandle);
}

#define OPEN_STACK_TRACK\
	HANDLE hThread = GetCurrentThread(); \
	GetThreadContext(hThread, &g_context); \
	__asm{call $ + 5}\
	__asm{pop eax}\
	__asm{mov g_context.Eip, eax}\
	__asm{mov g_context.Ebp, ebp}\
	__asm{mov g_context.Esp, esp}\
	InitTrack(); \
	StackTrack(); \
	UninitTrack();
static const char *getStack(int &len){
	OPEN_STACK_TRACK;
	len = strlen(tempbuffs);
	return tempbuffs;
}
#endif

TypeException::TypeException() :data(NULL)
{
	int len = 0;
	const char * p = getStack(len);
	data = new char[len+1];
	memcpy(data, p, len);
	data[len] = 0;
}

TypeException::~TypeException()
{
	delete data;
	data = NULL;
}
TypeException::TypeException(std::string var):data(NULL){
	int len = 0;
	const char * p = getStack(len);
	data = new char[len + 2+var.length()];
	memcpy(data, var.c_str(), var.length());
	data[var.length()] = '\n';
	memcpy(&data[var.length()+1], p, len);
	data[len + 1 + var.length()] = 0;
}