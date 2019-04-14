#include "pch.h"
#include "TOtherSys.h"
#include <fstream>


int Tinux::TCmdHello::run(std::vector<std::string>& outputBuff,std::vector<std::string>& errorBuff)
{
	outputBuff.push_back("Hello world!");
	return 0;
}

int Tinux::TCmdExit::run(std::vector<std::string>& outputBuff,std::vector<std::string>& errorBuff)
{
	exit(0);
}

int Tinux::TCmdHelp::run(std::vector<std::string>& outputBuff,std::vector<std::string>& errorBuff)
{
	std::string line;
	std::ifstream ifile("./etc/help.txt");
	if (ifile.is_open())
	{
		while (ifile.good())
		{
			getline(ifile, line);
			outputBuff.push_back(line);
		}
		ifile.close();
		return 0;
	}
	else
	{
		errorBuff.push_back("Help:/etc/help.txt not found");
		return -2;
	}
}
