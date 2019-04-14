#include "pch.h"
#include "Tash.h"
#include "TUtil.h"

#include <iostream>
#include "TCore.h"
#include <stdio.h>
#include <conio.h>
#include <direct.h>

using namespace std;

Tash::Tash()
{
}

Tash::~Tash()
{
}

void Tash::init()
{
	core.init();

	inputHelper.setCore(&core);
	inputHelper.init();
}

void Tash::run()
{
	string s1, s2;

	while (true)
	{
		std::cout << generatePrefix();

		string line = getInput();

		handleLine(line);
	}
}

std::string Tash::generatePrefix()
{
	std::string prefix;
	prefix += core.getUsername() + "@Tinux ";
	prefix += core.getCurPath();

	return prefix += ">";
}

void Tash::handleLine(std::string line)
{
	auto cmdLine = TUtil::split(line, " ");
	if (cmdLine.empty())
	{
		std::cout << std::endl;
		return;
	}

	std::vector<std::string> paraBox;
	for (size_t i = 1; i < cmdLine.size(); i++)
	{
		paraBox.push_back(cmdLine[i]);
	}

	int errCode = core.run(cmdLine[0], paraBox);

	if (errCode == 0)
	{
		output();
	}
	else
	{
		handleErrorCode(errCode);
	}
}

void Tash::handleErrorCode(int err)
{
	auto errorBuff = core.getErrorBuff();
	for (size_t i = 0; i < errorBuff.size(); i++)
	{
		std::cout << errorBuff[i] << std::endl;
	}
}

std::string Tash::getInput()
{
	return inputHelper.getInput();
}

void Tash::output()
{
	auto outputBuff = core.getOutputBuff();
	for (size_t i = 0; i < outputBuff.size(); i++)
	{
		std::cout << outputBuff[i] << std::endl;
	}
}
