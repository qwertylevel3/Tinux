#include "pch.h"
#include <direct.h>
#include <fstream>
#include <io.h>

#include "TCore.h"
#include "TFileSys.h"
#include "TOtherSys.h"

using namespace std;

Tinux::TCore::TCore()
{
}

Tinux::TCore::~TCore()
{
}

std::string Tinux::TCore::getUsername() const
{
	return username;
}

std::vector<std::string> Tinux::TCore::getOutputBuff() const
{
	return outputBuff;
}

std::vector<std::string> Tinux::TCore::getErrorBuff() const
{
	return errorBuff;
}

std::vector<std::string> Tinux::TCore::getAllCmd() const
{
	std::vector<std::string> allCmd;
	auto iter = cmdBox.begin();
	while (iter != cmdBox.end())
	{
		allCmd.push_back(iter->first);

		iter++;
	}
	return allCmd;
}

int Tinux::TCore::init(const std::string& pcPath /*= "./"*/)
{
	username = "admin";
	rootDir = pcPath;

	initCmd();

	homePath = rootDir + "home";
	userPath = rootDir + "home/" + username;
	etcPath = rootDir + "etc";
	binPath = rootDir + "bin";
	logPath = rootDir + "log";

	_mkdir(homePath.c_str());
	_mkdir(userPath.c_str());
	_mkdir(etcPath.c_str());
	_mkdir(binPath.c_str());
	_mkdir(logPath.c_str());

	//根目录的真实目录
	char buffer[260];
	_getcwd(buffer, 260);
	realRootPath = buffer;

	setCurPath(userPath);
	curPath = curPath.substr(1, curPath.length() - 1);

	return 0;
}

int Tinux::TCore::run(const std::string& cmd, std::vector<std::string>& paraBox)
{
	outputBuff.clear();
	errorBuff.clear();

	if (cmdBox.count(cmd) > 0)
	{
		cmdBox[cmd]->init();
		for (size_t i = 0; i < paraBox.size(); i++)
		{
			cmdBox[cmd]->addPara(paraBox[i]);
		}
		return cmdBox[cmd]->run(outputBuff, errorBuff);
	}
	else
	{
		errorBuff.push_back("TCore:command not found");
		return -1;
	}
}

std::string Tinux::TCore::path2realPath(std::string path)
{
	std::string cmpPath = path2Cmp(path);

	for (int i = 0; i < cmpPath.size(); i++)
	{
		if (cmpPath[i] == '/')
		{
			cmpPath[i] = '\\';
		}
	}

	return realRootPath + cmpPath;
}

std::string Tinux::TCore::realPath2path(std::string realPath)
{
	return realPath.replace(0, realRootPath.size(), "");
}

std::string Tinux::TCore::path2Cmp(std::string path)
{
	if (path.empty())
	{
		return "";
	}

	//首先将首个.转为当前目录
	//或者将首个..转换为上一级目录
	std::string curPathPre;
	if (path.size() >= 1)
	{
		if (path[0] != '.' && path[0] != '/')
		{
			path.insert(0, "./");
		}

		if (path.size() >= 2)
		{
			if (path[0] == '.' && path[1] == '.')
			{
				curPathPre = getPreDirectory(curPath);
				path.replace(0, 2, curPathPre);
			}
		}
		if (path[0] == '.')
		{
			if (curPath == "/")
			{
				if (path != ".")
				{
					path.replace(0, 1, "");
				}
				else
				{
					path = "/";
				}
			}
			else
			{
				path.replace(0, 1, curPath);
			}
		}
	}
	//然后将整个path中所有.和..全部替换
	//构造完整的逻辑目录
	vector<string> svec;

	size_t i = 0;
	size_t j = 0;

	j = path.find('/', j + 1);
	while (i != string::npos)
	{
		std::string curEle;
		if (j == string::npos)
		{
			curEle = path.substr(i + 1, path.size() - 1);
		}
		else
		{
			curEle = path.substr(i + 1, j - i - 1);
		}

		if (curEle == ".." && !svec.empty())
		{
			svec.pop_back();
		}
		else if (curEle != "." && curEle != "..")
		{
			svec.push_back(curEle);
		}

		i = j;
		j = path.find('/', j + 1);
	}
	std::string dispath;

	if (svec.empty())
	{
		dispath = "/";
	}
	else
	{
		for (int i = 0; i < svec.size(); i++)
		{
			dispath += "/";
			dispath += svec[i];
		}
	}
	return dispath;
}

std::string Tinux::TCore::getPreDirectory(const std::string& cmpPath)
{
	size_t pos = cmpPath.find_last_of('/');
	if (pos == 0)
	{
		return "/";
	}
	else if (pos == cmpPath.size() - 1)
	{
		pos = cmpPath.substr(0, cmpPath.size() - 1).find_last_of('/');
	}

	if (pos==0)
	{
		return "/";
	}

	return cmpPath.substr(0, pos);
}

std::vector<std::string> Tinux::TCore::listAll(const std::string& path)
{
	std::string realPath = this->path2realPath(path);

	vector<std::string> svec;

	//真实目录不存在
	if (_access(realPath.c_str(), 0) == -1)
	{
		return svec;
	}

	long hFile = 0;
	struct _finddata_t fileInfo;
	std::string pathName, exdName;
	// \\* 代表要遍历所有的类型,如改成\\*.jpg表示遍历jpg类型文件
	if ((hFile = _findfirst(pathName.assign(realPath).append("\\*").c_str(), &fileInfo)) == -1) {
		return svec;
	}
	do
	{
		//判断文件的属性是文件夹还是文件
		std::string name = fileInfo.name;

		if (name == "." || name == "..")
		{
			continue;
		}

		name += (fileInfo.attrib&_A_SUBDIR ? "/" : "");

		svec.push_back(name);
		//		cout << fileInfo.name << (fileInfo.attrib&_A_SUBDIR ? "[folder]" : "[file]") << endl;
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return svec;
}

void Tinux::TCore::initCmd()
{
	cmdBox["hello"] = TCmdPtr(new TCmdHello());
	cmdBox["exit"] = TCmdPtr(new TCmdExit());
	cmdBox["help"] = TCmdPtr(new TCmdHelp());
	cmdBox["ls"] = TCmdPtr(new TCmdLS());
	cmdBox["cd"] = TCmdPtr(new TCmdCD());
	cmdBox["cat"] = TCmdPtr(new TCmdCat());



	auto iter = cmdBox.begin();
	while (iter != cmdBox.end())
	{
		iter->second->setCore(this);
		iter++;
	}
}