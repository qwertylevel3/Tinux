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

		//run之前初始化一下
		//清理之前的参数缓存之类
		virtual int init();

		//需要显示的东西直接放到outputBuff中
		virtual int run(std::vector<std::string>& outputBuff,std::vector<std::string>& errorBuff) = 0;

		void addPara(const std::string& para);

		void setCore(TCore* tcore);
	protected:
		TCore* core{ nullptr };
		//参数
		std::vector<std::string> paraBox;
	};

	typedef std::shared_ptr<TCmd> TCmdPtr;
}

