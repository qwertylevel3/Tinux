#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "TCmd.h"

//操作核心
//不负责输入输出(由shell负责)
//只负责：
//1.命令管理
//2.进程管理
//3.基本权限与登录
//这里会将输出内容放到缓冲区中
//shell通过读取缓冲区来确定显示内容
namespace Tinux
{
	class TCore
	{
	public:
		TCore();
		~TCore();

		std::string getUsername() const;

		std::vector<std::string> getOutputBuff() const;
		std::vector<std::string> getErrorBuff() const;

		std::vector<std::string> getAllCmd() const;

		//////////////////////////////////////////////////////////////////////////
		//基本
		//////////////////////////////////////////////////////////////////////////

		//在真实pc目录下初始化,作为根目录
		//检查是否存在以下文件夹，不存在则创建:
		//1./bin
		//2./etc
		//3./home
		//4./log
		//同时在/etc/password中设置初始账号admin(密码:admin),home中创建admin文件夹
		int init(const std::string& pcPath = "./");

		//运行命令
		int run(const std::string& cmd, std::vector<std::string>& paraBox);

		//逻辑上的当前目录
		//如果需要真实值使用toReal转化一下
		std::string getCurPath() const { return curPath; }
		void setCurPath(std::string val) { curPath = val; }

		//逻辑path转为真实path
		std::string path2realPath( std::string path);

		//真实路径转换为逻辑路径
		std::string realPath2path(std::string realPath);

		//替换目录中所有.和..构造完整目录
		std::string path2Cmp(std::string path);
		
		//获取上一级目录(参数需要为完整目录)
		std::string getPreDirectory(const std::string& cmpPath);

		//ls
		std::vector<std::string> listAll(const std::string& path);
		//
//		//登录
//		//会和/etc/password中记录做对比，如果成功则登入系统
//		//此时cd到home下对应文件夹中
//		int login(const std::string& account, const std::string& pw);
//
//		//重启
//		void reboot();
//
//		//////////////////////////////////////////////////////////////////////////
//		//文件系统
//		//////////////////////////////////////////////////////////////////////////
//
//		//列出当前目录下文件夹和文件
//		void ls();
//
//		//定位到目录
//		int cd(const std::string& path);
//
//		//移动或者重命名
//		int mv(const std::string& file1, const std::string& file2);
//
//		//显示文本
//		int cat(const std::string& file);
//
//		//////////////////////////////////////////////////////////////////////////
//		//进程管理(没什么卵用)
//		//////////////////////////////////////////////////////////////////////////
//
//		//core为核心进程(pid=rand1 ppid=1)
//		//tash为最核心子进程（pid=rand2 ppid=rand1)
//		//其余进程从tash中派生(pid=rand3 ppid=rand2)
//
//		//显示当前所有进程
//		void ps();
//		//杀死某个进程
//		bool kill(int pid);
//
//		//////////////////////////////////////////////////////////////////////////
//		//杂项
//		//////////////////////////////////////////////////////////////////////////
//
//		//清屏
//		void clear();
//
//		//显示第page页帮助
//		void help(int page);

	protected:
		void initCmd();

		//一个为一行
		//输出缓冲区
		std::vector<std::string> outputBuff;
		//当前错误
		std::vector<std::string> errorBuff;

		std::unordered_map<std::string,TCmdPtr> cmdBox;

		std::string username;
		std::string rootDir;

		std::string homePath;
		std::string userPath;
		std::string etcPath;
		std::string logPath;
		std::string binPath;

		std::string curPath;

		std::string realRootPath;
	};
}
