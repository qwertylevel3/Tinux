#include "pch.h"
#include "TUtil.h"




std::vector<std::string> TUtil::split(std::string str, std::string token)
{
	std::vector<std::string> vect;
	int nend = 0;
	int nbegin = 0;
	while (nend != -1)
	{
		nend = str.find(token, nbegin);
		if (nend == -1)
		{
			auto temp = str.substr(nbegin, str.length() - nbegin);
			if (temp != "")
			{
				vect.push_back(temp);
			}
		}
		else
		{
			auto temp = str.substr(nbegin, nend - nbegin);
			if (temp != "")
			{
				vect.push_back(temp);
			}
		}
		nbegin = nend + 1;
	}
	return vect;
}

