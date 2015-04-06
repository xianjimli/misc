#include <iostream>

#ifndef VECTOR_H
#define VECTOR_H

class CVector
{
public:
	CVector(void);
	CVector(size_t init_size);
	~CVector(void);
	CVector(const CVector& other);
	CVector& operator=(const CVector& other);

public:
	bool append(int data);
	bool prepend(int data);
	bool insert(size_t index, int data);
	bool set(size_t index, int data);
	bool get(size_t index, int& data);

private:
	bool extend(int delta);

private:
	size_t m_used;
	size_t m_total;
	int*   m_array;
};

#endif/*VECTOR_H*/
