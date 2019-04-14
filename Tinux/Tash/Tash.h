#pragma once

#include <vector>
#include <string>
#include "TCore.h"
#include "InputHelper.h"

//����������shell
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


	//������������ʾǰ׺
	std::string generatePrefix();


	void handleLine( std::string line);
	void handleErrorCode(int err);

	std::string getInput();

	void output();
};


