#pragma once


#include "TCmd.h"

//�ļ�ϵͳ�������

namespace Tinux
{
	class TCmdLS :public TCmd
	{
	public:
		int run(std::vector<std::string>& outputBuff, std::vector<std::string>& errorBuff);
	};

	class TCmdCD:public TCmd
	{
	public:
		int run(std::vector<std::string>& outputBuff, std::vector<std::string>& errorBuff);
	};
	class TCmdCat:public TCmd
	{
	public:
		int run(std::vector<std::string>& outputBuff, std::vector<std::string>& errorBuff);
	};
	
}
