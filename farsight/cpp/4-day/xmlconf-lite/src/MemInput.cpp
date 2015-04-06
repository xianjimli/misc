#include "DebugUtil.h"
#include "MemInput.h"

COMM_BEGIN()

CMemInput::CMemInput()
{
	m_nPos = 0;
	m_nDataLen = 0;
	return;
}

CMemInput::~CMemInput()
{
	return;
}
	
bool CMemInput::SetData(const string& strData)
{
	this->Reset();
	m_strData = strData;
	m_nDataLen = strData.length();
	
	return true;	
}

bool CMemInput::Get(int &c)
{
	bool bRet =  false;
	ASSERT(m_nDataLen > 0);

	if(m_nPos < m_nDataLen)
	{
		c = m_strData[m_nPos];
		m_nPos++;
		bRet = true;
	}
	
	return bRet;
}

bool CMemInput::Unget(int c)
{
	bool bRet = false;
	ASSERT(m_nDataLen > 0);

	if(m_nPos >= 0 && m_nPos <= m_nDataLen && m_nDataLen > 0)
	{
		m_strData[m_nPos] = c;
		m_nPos--;
		bRet = true;
	}

	return bRet;
}

bool CMemInput::Reset(void)
{
	m_nPos = 0;
	m_nDataLen = 0;

	return true;
}

COMM_END()
