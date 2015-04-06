#include "FileStream.h"

namespace farsight {

CFileStream::CFileStream(void)
{
	m_fp = NULL;

	return;
}

CFileStream::~CFileStream(void)
{
	if(m_fp != NULL)
	{
		fclose(m_fp);
		m_fp = NULL;
	}

	return;
}

bool CFileStream::open(const char* url, const char* mode)
{
	this->close();

	m_fp = fopen(url, mode);

	return m_fp != NULL;
}

int  CFileStream::read(void* buffer, size_t length)
{
	int ret = -1;
	if(m_fp != NULL)
	{
		ret = fread(buffer, 1, length, m_fp);
	}

	return ret;
}

int  CFileStream::write(const void* buffer, size_t length)
{
	int ret = -1;
	if(m_fp != NULL)
	{
		ret = fwrite(buffer, 1, length, m_fp);
	}

	return ret;
}

int  CFileStream::seek(int offset)
{
	return 0;
}

bool CFileStream::flush(void) const
{
	return true;
}

int  CFileStream::tell(void) const
{
	return 0;
}

int  CFileStream::size(void) const
{
	return 0;
}

bool CFileStream::close(void)
{
	return true;
}

}

#ifdef FILE_STREAM_TEST
using namespace farsight;
int main(int argc, char* argv[])
{
	
	CFileStream stream;
	stream.open("./test.txt","wb+");
	stream.write("aaa", 3);
	stream.close();

	return 0;
}
#endif/*FILE_STREAM_TEST*/

