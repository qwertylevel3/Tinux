#pragma once


#include <vector>
#include <string>

namespace Tinux
{
	class TCore;
}

struct LineWord
{
	std::string word;
	int indexBegin;
	int indexEnd;
};

class InputHelper
{
public:
	InputHelper();
	~InputHelper();

	void init();

	std::string getInput();

	void setCore(Tinux::TCore* tcore);

protected:
	void initState();

	//////////////////////////////////////////////////////////////////////////
	//退格
	void handleBackspace(int ch);

	//回车
	void handleEnter(int ch);

	//tab
	void handleTab(int ch);

	//space
	void handleSpace(int ch);

	//other
	void handleChar(int ch);


	//////////////////////////////////////////////////////////////////////////

	Tinux::TCore* core;

	//所有可用命令
	std::vector<std::string> cmdList;

	//判断一个string是否为路径
	bool isPath(const std::string& word);

	//tab补全导致重新获取输入
	//这里不需要重置参数
	bool tabFlag{ false };

	//存放当前输入的word
	std::vector<LineWord> wordBox;

	//正在输入的词的游标
	//a为当前词首，b为当前词尾
	int lineIndexA, lineIndexB;

	//当前输入行
	std::string line;

	//当前键入tab数量
	int tabCount;
};



