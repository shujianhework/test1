#include "LoadExe.h"
#include <ctime>
#include <Windows.h>
#include <ImageHlp.h>
#include <winnt.h>
LoadExe::LoadExe(std::string path):file(path), filedata(NULL)
{
}
LoadExe::~LoadExe()
{
}

void LoadExe::NTHandle(IMAGE_NT_HEADERS *nt) {
}
void LoadExe::DOSHandle(_IMAGE_DOS_HEADER *dos) {
}
/************************************************************************/
/* ����:�����ڴ���Ե�ַ���ļ�ƫ�Ƶ�ת��������
stRVA��    �����ڴ����ƫ�Ƶ�ַ
lpFileBuf: �ļ���ʼ��ַ
���أ�ת������ļ�ƫ�Ƶ�ַ*/
/************************************************************************/
size_t RVAToOffset(size_t stRVA, PVOID lpFileBuf)
{
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)lpFileBuf;
	size_t stPEHeadAddr = (size_t)lpFileBuf + pDos->e_lfanew;
	PIMAGE_NT_HEADERS32 pNT = (PIMAGE_NT_HEADERS32)stPEHeadAddr;	//������	
	DWORD dwSectionCount = pNT->FileHeader.NumberOfSections;	//�ڴ�����С	
	DWORD dwMemoruAil = pNT->OptionalHeader.SectionAlignment;
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNT);	//�������нڵ���ʼ�����ַ��ƫ��ֵ��	
	DWORD  dwDiffer = 0;
	for (DWORD i = 0; i < dwSectionCount; i++) {
		//ģ���ڴ�������
		DWORD dwBlockCount = pSection[i].SizeOfRawData / dwMemoruAil;
		dwBlockCount += pSection[i].SizeOfRawData%dwMemoruAil ? 1 : 0;
		DWORD dwBeginVA = pSection[i].VirtualAddress;
		DWORD dwEndVA = pSection[i].VirtualAddress + dwBlockCount * dwMemoruAil;
		//���stRVA��ĳ��������
		if (stRVA >= dwBeginVA && stRVA < dwEndVA)
		{
			dwDiffer = stRVA - dwBeginVA;
			return pSection[i].PointerToRawData + dwDiffer;
		}
		else if (stRVA < dwBeginVA)//���ļ�ͷ��ֱ�ӷ���		
		{
			return stRVA;
		}
	}
		return 0;
}
void LoadExe::FILEHandle(IMAGE_FILE_HEADER *ifile) {
	std::cout << "��������:";
	if (ifile->Machine == IMAGE_FILE_MACHINE_UNKNOWN) std::cout << ifile->Machine << "����:" << "";
	//if(ifile->Machine == IMAGE_FILE_MACHINE_TARGET_HOST) std::cout << ifile->Machine <<"����:"<<"Useful for indicating we want to interact with the host and not a WoW guest.";
	if(ifile->Machine == IMAGE_FILE_MACHINE_I386       ) std::cout << ifile->Machine <<"����:"<<"Intel 386.";
	if(ifile->Machine == IMAGE_FILE_MACHINE_R3000      ) std::cout << ifile->Machine <<"����:"<<"MIPS little-endian, 0x160 big-endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_R4000      ) std::cout << ifile->Machine <<"����:"<<"MIPS little-endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_R10000     ) std::cout << ifile->Machine <<"����:"<<"MIPS little-endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_WCEMIPSV2  ) std::cout << ifile->Machine <<"����:"<<"MIPS little-endian WCE v2";
	if(ifile->Machine == IMAGE_FILE_MACHINE_ALPHA      ) std::cout << ifile->Machine <<"����:"<<"Alpha_AXP";
	if(ifile->Machine == IMAGE_FILE_MACHINE_SH3        ) std::cout << ifile->Machine <<"����:"<<"SH3 little-endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_SH3DSP     ) std::cout << ifile->Machine <<"����:"<<"";
	if(ifile->Machine == IMAGE_FILE_MACHINE_SH3E       ) std::cout << ifile->Machine <<"����:"<<"SH3E little-endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_SH4        ) std::cout << ifile->Machine <<"����:"<<"SH4 little-endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_SH5        ) std::cout << ifile->Machine <<"����:"<<"SH5";
	if(ifile->Machine == IMAGE_FILE_MACHINE_ARM        ) std::cout << ifile->Machine <<"����:"<<"ARM Little-Endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_THUMB      ) std::cout << ifile->Machine <<"����:"<<"ARM Thumb/Thumb-2 Little-Endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_ARMNT      ) std::cout << ifile->Machine <<"����:"<<"ARM Thumb-2 Little-Endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_AM33       ) std::cout << ifile->Machine <<"����:"<<"";
	if(ifile->Machine == IMAGE_FILE_MACHINE_POWERPC    ) std::cout << ifile->Machine <<"����:"<<"IBM PowerPC Little-Endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_POWERPCFP  ) std::cout << ifile->Machine <<"����:"<<"";
	if(ifile->Machine == IMAGE_FILE_MACHINE_IA64       ) std::cout << ifile->Machine <<"����:"<<"Intel 64";
	if(ifile->Machine == IMAGE_FILE_MACHINE_MIPS16     ) std::cout << ifile->Machine <<"����:"<<"MIPS";
	if(ifile->Machine == IMAGE_FILE_MACHINE_ALPHA64    ) std::cout << ifile->Machine <<"����:"<<"ALPHA64";
	if(ifile->Machine == IMAGE_FILE_MACHINE_MIPSFPU    ) std::cout << ifile->Machine <<"����:"<<"MIPS";
	if(ifile->Machine == IMAGE_FILE_MACHINE_MIPSFPU16  ) std::cout << ifile->Machine <<"����:"<<"MIPS";
	if(ifile->Machine == IMAGE_FILE_MACHINE_TRICORE    ) std::cout << ifile->Machine <<"����:"<<"Infineon";
	if(ifile->Machine == IMAGE_FILE_MACHINE_CEF        ) std::cout << ifile->Machine <<"����:"<<"";
	if(ifile->Machine == IMAGE_FILE_MACHINE_EBC        ) std::cout << ifile->Machine <<"����:"<<"EFI Byte Code";
	if(ifile->Machine == IMAGE_FILE_MACHINE_AMD64      ) std::cout << ifile->Machine <<"����:"<<"AMD64 (K8)";
	if(ifile->Machine == IMAGE_FILE_MACHINE_M32R       ) std::cout << ifile->Machine <<"����:"<<"M32R little-endian";
	//if(ifile->Machine == IMAGE_FILE_MACHINE_ARM64      ) std::cout << ifile->Machine <<"����:"<<"ARM64 Little-Endian";
	if(ifile->Machine == IMAGE_FILE_MACHINE_CEE        ) std::cout << ifile->Machine <<"����:"<<"";
	std::cout << "\n���ļ�����:";
	int fileExFlg = ifile->Characteristics;
	if (fileExFlg == IMAGE_FILE_RELOCS_STRIPPED			  )std::cout << "Relocation info stripped from file";
	if ( fileExFlg == IMAGE_FILE_EXECUTABLE_IMAGE         )std::cout << "File is executable  (i.e. no unresolved external references).";
	if ( fileExFlg == IMAGE_FILE_LINE_NUMS_STRIPPED       )std::cout << "Line nunbers stripped from file.";
	if ( fileExFlg == IMAGE_FILE_LOCAL_SYMS_STRIPPED      )std::cout << "Local symbols stripped from file.";
	if ( fileExFlg == IMAGE_FILE_AGGRESIVE_WS_TRIM        )std::cout << "Aggressively trim working set";
	if ( fileExFlg == IMAGE_FILE_LARGE_ADDRESS_AWARE      )std::cout << "App can handle >2gb addresses";
	if ( fileExFlg == IMAGE_FILE_BYTES_REVERSED_LO        )std::cout << "Bytes of machine word are reversed.";
	if ( fileExFlg == IMAGE_FILE_32BIT_MACHINE            )std::cout << "32 bit word machine.";
	if ( fileExFlg == IMAGE_FILE_DEBUG_STRIPPED           )std::cout << "Debugging info stripped from file in .DBG file";
	if ( fileExFlg == IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP  )std::cout << "If Image is on removable media, copy and run from the swap file.";
	if ( fileExFlg == IMAGE_FILE_NET_RUN_FROM_SWAP        )std::cout << "If Image is on Net, copy and run from the swap file.";
	if ( fileExFlg == IMAGE_FILE_SYSTEM                   )std::cout << "System File.";
	if ( fileExFlg == IMAGE_FILE_DLL                      )std::cout << "File is a DLL.";
	if ( fileExFlg == IMAGE_FILE_UP_SYSTEM_ONLY           )std::cout << "File should only be run on a UP machine";
	if ( fileExFlg == IMAGE_FILE_BYTES_REVERSED_HI		  )std::cout << "Bytes of machine word are reversed.";
	std::cout << "\n����������"<<ifile->NumberOfSections;
	time_t t = ifile->TimeDateStamp;
	auto tp = localtime(&t);
	char arr[1024] = "";
	sprintf(arr, "%d��%d��%d�� %dʱ%d��%d��", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
	std::cout << "����ʱ��:" << arr;
}
void LoadExe::OPTIONALHandle(IMAGE_OPTIONAL_HEADER *opt) {
	if (opt->Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
		std::cout << "�ļ� 32λ����"<<std::endl;
	else
		std::cout << "�ļ� 64λ����" << std::endl;
	std::cout << "�汾:" << opt->MinorImageVersion << "." << opt->MinorImageVersion << std::endl;
	std::cout << "��������С" << opt->SizeOfCode<<std::endl;
	std::cout << "��ʼ�����ݴ�С" << opt->SizeOfInitializedData<<std::endl;
	std::cout << "δ��ʼ�����ݴ�С:" << opt->SizeOfUninitializedData << std::endl;
	std::cout << "RVA������ڵ�ַ:" << opt->AddressOfEntryPoint << std::endl;
	std::cout << "RVA����ε�ַ:" << opt->BaseOfCode << std::endl;
	std::cout << "RVA���ݶε�ַ:" << opt->BaseOfCode << std::endl;
	std::cout << "�����:" << opt->NumberOfRvaAndSizes << std::endl;
	//ֱ�ӿ����һ��
	for (int i = 0; i < opt->NumberOfRvaAndSizes; i++)
	{
		IMAGE_DATA_DIRECTORY dire = opt->DataDirectory[i];
		std::cout << "��" << i << "����"<< dire.VirtualAddress << " size = " << dire.Size<<"����";
		switch (i)
		{
		case IMAGE_DIRECTORY_ENTRY_EXPORT: {
			std::cout << "������";
			int offset = RVAToOffset(dire.VirtualAddress, filedata);
			IMAGE_EXPORT_DIRECTORY *Export = (IMAGE_EXPORT_DIRECTORY*)(filedata + offset);
			std::cout<< filedata+RVAToOffset(Export->Name,filedata)<<std::endl;
			char *namebegin = (char*)(filedata + RVAToOffset(Export->AddressOfNameOrdinals + Export->NumberOfNames * 2, filedata));
			char arrbuff[256] = "";
			for (size_t i = 0; i < Export->NumberOfNames; i++)
			{
				namebegin = namebegin + strlen(namebegin) + 1;
				//std::cout << "\""<<namebegin<<"\"," << std::endl;
				UnDecorateSymbolName(namebegin, arrbuff, 255, 0);
				std::cout << arrbuff << std::endl;
			}
		}break;
		case IMAGE_DIRECTORY_ENTRY_IMPORT: {
			int offset = RVAToOffset(dire.VirtualAddress, filedata);
			IMAGE_IMPORT_DESCRIPTOR *Import = (IMAGE_IMPORT_DESCRIPTOR*)(filedata + offset);
			
			for (int i = 0; i > -1; i++){
				IMAGE_IMPORT_DESCRIPTOR *Import2 = Import+i;
				int offset = RVAToOffset(Import2->Name, filedata);
				if (offset > 0 ){//&& offset < opt->SizeOfCode){
					std::string Names = filedata + offset;
					if (Names.size()>3 && (Names.find(".lib") != Names.npos || Names.find(".LIB") != Names.npos || Names.find(".dll") != Names.npos || Names.find(".DLL") != Names.npos)){
						std::cout << Names << std::endl;
					}
					else
					{
						i = -2;
					}
				}
				else i = -2;
				
			}
		}
		default:
			break;
		}
	}

}
//void LoadExe::ROMHandle(IMAGE_ROM_OPTIONAL_HEADER *rom) {
//}
static char *getdata(std::string path) {
	char *p = NULL;
#ifndef UserWin32 
	HANDLE f = CreateFile(path.c_str(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (f == INVALID_HANDLE_VALUE)
		return p;
	DWORD size1 = 4096000;
	DWORD size2 = 0;
	size1 = GetFileSize(f, &size2);
	if (size2 > 0)
	{
		CloseHandle(f);
		return p;
	}
	p = new char[size1 + 100];
	if (ReadFile(f, p, size1, &size2, NULL) == FALSE)
	{
		delete p;
		p = NULL;
		CloseHandle(f);
		return p;
	}
	CloseHandle(f);
#else
	FILE *f = fopen(path.c_str(), "rb");
	if (f == NULL)
		return p;
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);
	p = new char[size+1];
	
	if (fread(p, sizeof(char), size, f) < 0)
	{
		delete p;
		p = NULL;
	}
	fclose(f);
	f = NULL;
#endif
	return p;
}
void LoadExe::run() {
	char * p = getdata(file);
	if (p == NULL)
		return;
	this->filedata = p;
	_IMAGE_DOS_HEADER* idh = (_IMAGE_DOS_HEADER*)p;
	this->DOSHandle(idh);
	if (idh->e_magic == IMAGE_DOS_SIGNATURE) {
		IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS*)(p + (idh->e_lfanew));
		this->NTHandle(nt);
		this->FILEHandle(&nt->FileHeader);
		this->OPTIONALHandle(&nt->OptionalHeader);
		/*if (nt->Signature == IMAGE_NT_SIGNATURE) {
			std::cout << "����һ��pe�ļ�" << std::endl;
			if (nt->FileHeader.NumberOfSections > 0) {				
			}
		}*/
		/*IMAGE_SECTION_HEADER *headsection = NULL;
		for (size_t i = 0; i < nt->FileHeader.NumberOfSections; i++)
		{
			headsection =  (IMAGE_SECTION_HEADER*)(filedata + idh->e_lfanew + sizeof(IMAGE_NT_HEADERS) + i * sizeof(IMAGE_SECTION_HEADER));
			std::cout << "��������:" << headsection->Name<<std::endl;
		}*/
	}
	delete p;
	p = NULL;
	filedata = NULL;
}
void LoadExe::test() {
	auto p = LoadLibrary(file.c_str());
	typedef  int (*Add)(int, int);
	Add add = (Add)GetProcAddress(p, "add");
	int jl = add(2, 3);
	std::cout << "2+3 = " << jl;
	FreeLibrary(p);
}