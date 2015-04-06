//build:gcc -g  IsBracketMatch.cpp -Wall -lstdc++ -o IsBracketMatch.exe 
#include <stack>
#include <string>
#include <iostream>

using namespace std;

bool IsBracketMatch(const string& str)
{
	size_t i = 0;
	size_t n = str.length();
	stack<char> stk;
	
	for(i = 0; i < n; i++)
	{
		if(str[i] == '{')
		{
			stk.push(str[i]);
		}
		else if(str[i] == '}')
		{
			if(!stk.empty())
			{
				stk.pop();
			}
			else
			{
				break;
			}
		}
		else
		{
			continue;
		}
	}

	return i == n && stk.empty();
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cout <<"Usage: " << argv[0] << " [string] " <<endl;
		cout <<"Check if the left bracket and right bracket are matched." <<endl;
	}
	else
	{
		if(IsBracketMatch(argv[1]))
		{
			cout<<"accept: " << argv[1] << endl;
		}
		else
		{
			cout<<"reject: " << argv[1] << endl;
		}
	}

	return 0;
}

