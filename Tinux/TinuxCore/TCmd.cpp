#include "pch.h"
#include "TCmd.h"


Tinux::TCmd::TCmd()
{
}


Tinux::TCmd::~TCmd()
{
}

int Tinux::TCmd::init()
{
	paraBox.clear();
	return 0;
}

void Tinux::TCmd::addPara(const std::string& para)
{
	paraBox.push_back(para);
}

void Tinux::TCmd::setCore(TCore* tcore)
{
	core = tcore;
}

