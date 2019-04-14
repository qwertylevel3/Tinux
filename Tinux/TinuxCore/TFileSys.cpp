#include "pch.h"
#include "TFileSys.h"
#include "TUtil.h"
#include "TCore.h"
#include <iostream>
#include <io.h>

using namespace std;



int Tinux::TCmdCD::run(std::vector<std::string>& outputBuff, std::vector<std::string>& errorBuff)
{
	if (paraBox.empty())
	{
		return 0;
	}
	std::string curPath = core->getCurPath();
	std::string disPath = paraBox[0];

	std::string realDisPath = core->path2realPath(disPath);
//	outputBuff.push_back(realDisPath);
	if (_access(realDisPath.c_str(), 0) == -1)
	{
		errorBuff.push_back("cd : dictionary is not exist!");
	}
	else
	{
//		outputBuff.push_back(core->path2Cmp(disPath));
		core->setCurPath(core->path2Cmp(disPath));
	}

	return 0;
}

int Tinux::TCmdLS::run(std::vector<std::string>& outputBuff, std::vector<std::string>& errorBuff)
{
	auto svec = core->listAll(core->getCurPath());

	for (int i=0;i<svec.size();i++)
	{
		outputBuff.push_back(svec[i]);
	}

	return 0;
}