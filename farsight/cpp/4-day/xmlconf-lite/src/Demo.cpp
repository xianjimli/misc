#include <iostream>
using namespace std;
#include "XmlConfig.h"

USE_XML;

int main(int argc, char* argv[])
{
	CXmlConfig aXmlConfig;
	if(argc != 4)
	{
		cout << "Usage: " << argv[0] <<"[file] [xpath] [value]" << endl;
		cout << "for example:" << argv[0] << " demo.xml /window/width/#text 1000" << endl;

		return 1;
	}

	string strFileName = argv[1];
	string strXPath = argv[2];
	string strValue = argv[3];

	if(aXmlConfig.Open(strFileName, true))
	{
		string str;
		if(aXmlConfig.Get(strXPath, str))
		{
			cout<< "old: " <<strXPath<< " is " <<str << endl;
		}
		else
		{
			cout<< strXPath <<" not exist"<< endl;
		}
		
		if(!aXmlConfig.Set(strXPath, strValue, true))
		{
			cout << "aXmlConfig.Set failed." << endl;
		}

		if(aXmlConfig.Get(strXPath, str))
		{
			cout<<"new: " << strXPath << " is " << str <<endl;
		}
		else
		{
			cout<<"aXmlConfig.Get"<<endl;
		}

		aXmlConfig.Save("lxj.xml", true);
	}
	
	return 0;
}
