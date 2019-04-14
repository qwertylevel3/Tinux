#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "TCmd.h"

//��������
//�������������(��shell����)
//ֻ����
//1.�������
//2.���̹���
//3.����Ȩ�����¼
//����Ὣ������ݷŵ���������
//shellͨ����ȡ��������ȷ����ʾ����
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
		//����
		//////////////////////////////////////////////////////////////////////////

		//����ʵpcĿ¼�³�ʼ��,��Ϊ��Ŀ¼
		//����Ƿ���������ļ��У��������򴴽�:
		//1./bin
		//2./etc
		//3./home
		//4./log
		//ͬʱ��/etc/password�����ó�ʼ�˺�admin(����:admin),home�д���admin�ļ���
		int init(const std::string& pcPath = "./");

		//��������
		int run(const std::string& cmd, std::vector<std::string>& paraBox);

		//�߼��ϵĵ�ǰĿ¼
		//�����Ҫ��ʵֵʹ��toRealת��һ��
		std::string getCurPath() const { return curPath; }
		void setCurPath(std::string val) { curPath = val; }

		//�߼�pathתΪ��ʵpath
		std::string path2realPath( std::string path);

		//��ʵ·��ת��Ϊ�߼�·��
		std::string realPath2path(std::string realPath);

		//�滻Ŀ¼������.��..��������Ŀ¼
		std::string path2Cmp(std::string path);
		
		//��ȡ��һ��Ŀ¼(������ҪΪ����Ŀ¼)
		std::string getPreDirectory(const std::string& cmpPath);

		//ls
		std::vector<std::string> listAll(const std::string& path);
		//
//		//��¼
//		//���/etc/password�м�¼���Աȣ�����ɹ������ϵͳ
//		//��ʱcd��home�¶�Ӧ�ļ�����
//		int login(const std::string& account, const std::string& pw);
//
//		//����
//		void reboot();
//
//		//////////////////////////////////////////////////////////////////////////
//		//�ļ�ϵͳ
//		//////////////////////////////////////////////////////////////////////////
//
//		//�г���ǰĿ¼���ļ��к��ļ�
//		void ls();
//
//		//��λ��Ŀ¼
//		int cd(const std::string& path);
//
//		//�ƶ�����������
//		int mv(const std::string& file1, const std::string& file2);
//
//		//��ʾ�ı�
//		int cat(const std::string& file);
//
//		//////////////////////////////////////////////////////////////////////////
//		//���̹���(ûʲô����)
//		//////////////////////////////////////////////////////////////////////////
//
//		//coreΪ���Ľ���(pid=rand1 ppid=1)
//		//tashΪ������ӽ��̣�pid=rand2 ppid=rand1)
//		//������̴�tash������(pid=rand3 ppid=rand2)
//
//		//��ʾ��ǰ���н���
//		void ps();
//		//ɱ��ĳ������
//		bool kill(int pid);
//
//		//////////////////////////////////////////////////////////////////////////
//		//����
//		//////////////////////////////////////////////////////////////////////////
//
//		//����
//		void clear();
//
//		//��ʾ��pageҳ����
//		void help(int page);

	protected:
		void initCmd();

		//һ��Ϊһ��
		//���������
		std::vector<std::string> outputBuff;
		//��ǰ����
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
