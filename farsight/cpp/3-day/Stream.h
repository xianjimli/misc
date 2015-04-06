#include <iostream>

#ifndef STREAM_H
#define STREAM_H

namespace farsight {

class CStream
{
public:
	CStream(void);
	virtual ~CStream(void);
	
public:
	virtual bool open(const char* args, const char* mode) = 0;
	virtual int read(void* buffer, size_t length) = 0;
	virtual int write(const void* buffer, size_t length) = 0;
	virtual int seek(int offset) = 0;
	virtual bool flush(void) const = 0;
	virtual int tell(void) const = 0;
	virtual int size(void) const = 0;
	virtual bool close(void) = 0;

private:
	CStream(const CStream& other);
	CStream& operator=(const CStream& other);
};

}/*farsight*/

#endif/*STREAM_H*/

