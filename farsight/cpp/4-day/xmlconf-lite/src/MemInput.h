#ifndef COMM_MEM_INPUT_H
#define COMM_MEM_INPUT_H

#include <string>
using std::string;

#include "Input.h"

COMM_BEGIN()
	
class COMM_API CMemInput: public CInput
{
public:
	CMemInput();
	~CMemInput();
public:
	bool SetData(const string& strData);

	bool Get(int &c);
	bool Unget(int c);
private:
	bool Reset(void);	
private:
	string m_strData;
	size_t m_nPos;
	size_t m_nDataLen;
};

COMM_END()

#endif//COMM_MEM_INPUT_H
