#include "ListArgs.h"
#include "libcjson\cJSON.h"

ListArgs::ListArgs(std::string param)
{
	this->argv.clear();
	if (param.size() > 0){
		cJSON *cjson = cJSON_Parse(param.c_str());
		if (cjson == NULL){
			throw std::exception("��������ʧ�� NULL");
		}
		if (cJSON_IsArray(cjson) == false){
			throw std::exception("�������������� NULL");
		}
		int size = cJSON_GetArraySize(cjson);
		for (int i = 0; i < size; i++)
		{
			cJSON *item = cJSON_GetArrayItem(cjson, i);
			std::string str = "";
			if (item->string == NULL)
			{
				if (cJSON_IsObject(item) == true)
					throw std::exception("����ֻ���������������(int[],string[],double[],bool[])");
				if (cJSON_IsNumber(item))
				{
					char arr[100] = { 0 };
					double num = item->valuedouble;
					sprintf_s(arr, "%g", num);
					str = arr;
				}
			}
			else
				str = cJSON_GetStringValue(item);
			argv.push_back(str.c_str());
		}
	}
}


ListArgs::~ListArgs()
{
}
#define CHECKTHROW(idx) if(argv.size() <= idx) throw std::exception("�±곬��");
int ListArgs::getInt(unsigned int idx){
	CHECKTHROW(idx);
	long long ret = _atoi64(argv[idx].c_str());
	return (int)ret;
}

unsigned int ListArgs::getUInt(unsigned int idx){
	CHECKTHROW(idx);
	long long ret = _atoi64(argv[idx].c_str());
	return (unsigned int)ret;
}
double ListArgs::getdouble(unsigned int idx){
	CHECKTHROW(idx);
	double ret = atof(argv[idx].c_str());
	return ret;
}
float ListArgs::getfloat(unsigned int idx){
	CHECKTHROW(idx);
	float ret = atof(argv[idx].c_str());
	return ret;
}
std::string ListArgs::getstring(unsigned int idx){
	CHECKTHROW(idx);
	std::string str = argv[idx].c_str();
	return str;
}
bool ListArgs::getbool(unsigned int idx){
	CHECKTHROW(idx);
	std::string str = argv[idx].c_str();
	if (str == "0" || str == "false" || str == "False" || str == "FALSE" || str == "��")
		return false;
	return true;
}