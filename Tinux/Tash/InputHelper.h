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
	//�˸�
	void handleBackspace(int ch);

	//�س�
	void handleEnter(int ch);

	//tab
	void handleTab(int ch);

	//space
	void handleSpace(int ch);

	//other
	void handleChar(int ch);


	//////////////////////////////////////////////////////////////////////////

	Tinux::TCore* core;

	//���п�������
	std::vector<std::string> cmdList;

	//�ж�һ��string�Ƿ�Ϊ·��
	bool isPath(const std::string& word);

	//tab��ȫ�������»�ȡ����
	//���ﲻ��Ҫ���ò���
	bool tabFlag{ false };

	//��ŵ�ǰ�����word
	std::vector<LineWord> wordBox;

	//��������Ĵʵ��α�
	//aΪ��ǰ���ף�bΪ��ǰ��β
	int lineIndexA, lineIndexB;

	//��ǰ������
	std::string line;

	//��ǰ����tab����
	int tabCount;
};



