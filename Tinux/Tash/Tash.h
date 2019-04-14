#pragma once

#include <vector>
#include <string>
#include "TCore.h"
#include "InputHelper.h"

//基本命令行shell
class Tash
{
public:
	Tash();
	~Tash();

	void init();

	void run();
protected:
	Tinux::TCore core;

	InputHelper inputHelper;


	//生成命令行提示前缀
	std::string generatePrefix();


	void handleLine( std::string line);
	void handleErrorCode(int err);

	std::string getInput();

	void output();
};


