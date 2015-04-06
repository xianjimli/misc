#include "Stream.h"

#ifndef FILE_STREAM_H
#define FILE_STREAM_H

namespace farsight {

class CFileStream : public CStream
{
public:
	CFileStream(void);
	virtual ~CFileStream(void);

public:
	virtual bool open(const char* args, const char* mode);
	virtual int  read(void* buffer, size_t length);
	virtual int  write(const void* buffer, size_t length);
	virtual int  seek(int offset);
	virtual bool flush(void) const;
	virtual int  tell(void) const;
	virtual int  size(void) const;
	virtual bool close(void);

private:
	FILE* m_fp;
};

}/*farsight*/

#endif/*FILE_STREAM_H*/

