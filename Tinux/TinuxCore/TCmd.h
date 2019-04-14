#pragma once

#include <vector>
#include <string>
#include <memory>



namespace Tinux
{
	class TCore;

	class TCmd
	{
	public:
		TCmd();
		virtual ~TCmd();

		//run֮ǰ��ʼ��һ��
		//����֮ǰ�Ĳ�������֮��
		virtual int init();

		//��Ҫ��ʾ�Ķ���ֱ�ӷŵ�outputBuff��
		virtual int run(std::vector<std::string>& outputBuff,std::vector<std::string>& errorBuff) = 0;

		void addPara(const std::string& para);

		void setCore(TCore* tcore);
	protected:
		TCore* core{ nullptr };
		//����
		std::vector<std::string> paraBox;
	};

	typedef std::shared_ptr<TCmd> TCmdPtr;
}

