#include "pch.h"
#include "InputHelper.h"
#include "TCore.h"

#include <iostream>
#include "TCore.h"
#include <stdio.h>
#include <conio.h>
#include <direct.h>

using namespace std;

InputHelper::InputHelper()
{
}

InputHelper::~InputHelper()
{
}

void InputHelper::init()
{
	cmdList = core->getAllCmd();
}

std::string InputHelper::getInput()
{
	//重设置参数
	if (!tabFlag)
	{
		initState();
	}
	else
	{
		tabFlag = false;

		printf("%s", line.c_str());
	}

	while (true) {
		int ch = _getch();

		if (ch == 8) //退格
		{
			handleBackspace(ch);
		}
		else if (ch == 13)//回车
		{
			handleEnter(ch);
			return line;
		}
		else if (ch == 9) //tab
		{
			handleTab(ch);
			if (tabFlag)
			{
				return "";
			}
		}
		else if (ch == ' ') {
			handleSpace(ch);
		}
		else {
			handleChar(ch);
		}

		if (ch == 9) {
			tabCount++;
		}
		else {
			tabCount = 0;
		}
	}
}

void InputHelper::setCore(Tinux::TCore* tcore)
{
	core = tcore;
}

void InputHelper::initState()
{
	lineIndexA = 0;
	lineIndexB = 0;
	line = "";
	tabCount = 0;
}

void InputHelper::handleBackspace(int ch)
{
	if (!line.empty())
	{
		line.pop_back();
		printf("%c", 8);
		printf(" ");
		printf("%c", 8);

		lineIndexB--;

		if (!wordBox.empty())
		{
			LineWord lastWord = wordBox[wordBox.size() - 1];
			if (lineIndexB < lastWord.indexEnd)
			{
				lineIndexA = lastWord.indexBegin;

				wordBox.pop_back();
			}
		}
	}
}

void InputHelper::handleEnter(int ch)
{
	printf("\n");
}

void InputHelper::handleTab(int ch)
{
	std::string curWord = line.substr(lineIndexA, lineIndexB - lineIndexA);
	std::vector<std::string> cmpWordList;//补全列表

	if (wordBox.empty())//如果是第一个word,则可以补全cmd
	{
		cmpWordList = cmdList;
	}
	else//否则补全路径
	{
		std::string prePath;
		std::string lastPath;
		if (isPath(curWord))
		{
			auto index = curWord.find_last_of('/');
			prePath = curWord.substr(0, index);
			lastPath = curWord.substr(index + 1, curWord.size() - index - 1);
		}
		else
		{
			prePath = "./";
			lastPath = curWord;
		}
		cmpWordList = core->listAll(prePath);
		curWord = lastPath;
	}

	vector<int> satisfyBox;
	for (int i = 0; i < cmpWordList.size(); i++) {
		if (cmpWordList[i].length() >= curWord.length() && cmpWordList[i].substr(0, curWord.length()) == curWord) {
			satisfyBox.push_back(i);
		}
	}

	if (satisfyBox.size() == 1) {
		//只有一个满足，直接补全
		for (int i = curWord.length(); i < cmpWordList[satisfyBox[0]].length(); i++) {
			line.push_back(cmpWordList[satisfyBox[0]][i]);
			printf("%c", cmpWordList[satisfyBox[0]][i]);
			lineIndexB++;
		}
	}
	if (satisfyBox.size() > 1 && tabCount) {
		//多个满足
		cout << "\n" << cmpWordList[satisfyBox[0]];
		for (int i = 1; i < satisfyBox.size(); i++) {
			cout << "    " << cmpWordList[satisfyBox[i]];
		}
		cout << endl;

		tabFlag = true;
	}
}

void InputHelper::handleSpace(int ch)
{
	LineWord word;
	word.indexBegin = lineIndexA;
	word.indexEnd = lineIndexB;
	word.word = line.substr(lineIndexA, lineIndexB - lineIndexA);

	if (!word.word.empty())
	{
		wordBox.push_back(word);
	}

	lineIndexB++;
	lineIndexA = lineIndexB;

	printf("%c", ch);
	line.push_back(ch);
}

void InputHelper::handleChar(int ch)
{
	lineIndexB++;

	printf("%c", ch);
	line.push_back(ch);
}

bool InputHelper::isPath(const std::string& word)
{
	if (!word.empty() && (word[0] == '/' || word[0] == '.'))
	{
		return true;
	}
	return false;
}