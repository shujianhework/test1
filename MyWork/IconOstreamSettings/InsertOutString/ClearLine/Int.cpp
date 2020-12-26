#include "stdafx.h"
#include "Int.h"
Int Int::parse(const char *p, int len) throw(TypeException){
	if (p == NULL)
		throw TypeException("nil Cannot convert Int");
	if (len == 0)
		len = strlen(p);
	char *p1 = (char*)p;
	if (p[0] == '-'){
		p1 = &p1[1];
		len--;
	}
	//10进制  8进制  16进制
	char System = 0;
	if (len < 2 && (p1[1] <= '9' && p1[0] >= '0'))//1 
		System = 10;
	else if (len < 3){
		if (p1[0] == '0')
			System = 8;
		else if (p1[1] <= '9' && p1[0] > '0')
			System = 10;
		else
			System = 0;
	}
	else{
		if (p1[0] == '0'){
			if (p1[1] == 'x' || p1[1] == 'X'){
				System = 16;
			}else if (p1[1] < '8' && p1[0] >= '0'){
				System = 8;
			}
		}
		else if (p1[1] <= '9' && p1[0] > '0'){
			System = 10;
		}
	}
	if (System == 0)
		throw TypeException("Undefined base");
	switch (System)
	{
	case 8:{
			   p1++;
			   len--;
	}
		break;
	case 16:{
				p1+=2;
				len-=2;
	}
		break;
	}
	long long val = 0;
	for (int i = 0; i < len; i++)
	{
		char c = p1[i];
		if (c < '8' && c >= '0'){
			val = val * System + (c - '0');
		}
		else if (System > 8 && c <= '9'){
			val = val * System + (c - '0');
		}
		else if (System == 16 && (c >= 'a' && c <= 'e')){
			val = val * System + (c - 'a') + 10;
		}
		else if (System == 16 && (c >= 'A' && c <= 'E')){
			val = val * System + (c - 'A') + 10;
		}
		else{
			char arr[100] = " ";
			sprintf_s(arr, "Int.parse() Param error char %c in base = %d", c, System);
			TypeException *tp = new TypeException(arr);
			throw tp;
			delete tp;
			tp = NULL;
		}
	}
	if (p[0] == '-')
		val = 0 - val;
	return Int(val);
}