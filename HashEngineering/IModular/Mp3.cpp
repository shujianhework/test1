#include "Mp3.h"
#include <Windows.h>

Mp3::Mp3(std::string path) :JHFile(path),id3v2(NULL)
{
	if (datalen > 0){
	}
}
#define Name2Id2Map(namekey,a,b) if(strlen(namekey) == 4)\
{int hashid = *(int*)namekey;\
	strncpy_s((char*)framedata, 2000,(const char*)&data[idx+a],b);framedata[b] = 0;this->FrameInfos.insert(std::make_pair(hashid, framedata));}
void Mp3::init(){
	if (id3v2 == NULL && data){
		id3v2 = (ID3V2*)data;
		char framedata[2001] = { 0 };
		if (strncmp(id3v2->Header, "ID3", 3) == 0){
			if (id3v2->Ver > 0 && id3v2->Ver < 5){
				//ID3V 验证通过
				int total_size;
				total_size = (id3v2->Size[0] & 0x7F) * 0x200000
					+ (id3v2->Size[1] & 0x7F) * 0x400
					+ (id3v2->Size[2] & 0x7F) * 0x80
					+ (id3v2->Size[3] & 0x7F);
				std::cout << "标签大小为:" << total_size << std::endl;
				int idx = sizeof(ID3V2);
				ID3V2Frame *frame = NULL;
				while (total_size>0){
					frame = (ID3V2Frame*)&data[idx];
					total_size -= sizeof(ID3V2Frame);
					if ((unsigned int)(frame->Frame) == 0){
						idx += sizeof(ID3V2);
						connect;
					}
					int framesize = frame->Size[0] * 0x100000000 + frame->Size[1] * 0x10000 + frame->Size[2] * 0x100 + frame->Size[3];
					total_size -= framesize;
					
					if (total_size < 0){
						break;
					}
					char arr[5] = { frame->Frame[0], frame->Frame[1], frame->Frame[2], frame->Frame[3] ,0};
					strncpy_s(framedata, 2000, (char*)&data[idx+sizeof(ID3V2Frame)+1], framesize-1);
					framedata[framesize >= 2000 ? 2000 : framesize] = 0;
					idx += sizeof(ID3V2Frame);
					idx += framesize;
					int hash = *(int*)frame->Frame;
					if (hash > 0)
						this->FrameInfos.insert(std::make_pair(hash, framedata));
				}
				idx = this->datalen - 128;
				if (data[idx] == 'T' && data[idx + 1] == 'A' && data[idx + 2] == 'G'){
					Name2Id2Map("name", 4, 30);
					Name2Id2Map("auth", 34,30);
					Name2Id2Map("zhua", 64,30 );
					Name2Id2Map("year", 94, 4);
					Name2Id2Map("othe", 98, 28);
					Name2Id2Map("othe", 98, 28);
					Name2Id2Map("NumI", 127,1);
					Name2Id2Map("Type", 128, 1);
				}
			}
		}
	}
	for each (auto var in this->FrameInfos)
	{
		std::cout << var.second << std::endl;
	}
}

Mp3::~Mp3()
{
}
