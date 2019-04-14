#pragma once


#include "TCmd.h"

namespace Tinux
{
	class TCmdHello:public TCmd
	{
	public:
		int run(std::vector<std::string>& outputBuff,std::vector<std::string>& errorBuff);
	};

	class TCmdExit:public TCmd
	{
	public:
		int run(std::vector<std::string>& outputBuff,std::vector<std::string>& errorBuff);
	};

	class TCmdHelp:public TCmd
	{
	public:
		int run(std::vector<std::string>& outputBuff,std::vector<std::string>& errorBuff);
	};
}