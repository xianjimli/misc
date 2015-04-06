#include "Vector.h"
#include <cstring>
#include <cstdlib>

CVector::CVector(void)
{
	m_used  = 0;
	m_total = 0;
	m_array = NULL;

	return;
}

CVector::CVector(size_t init_size)
{
	m_used  = 0;
	m_total = init_size;

	if(init_size > 0)
	{
		m_array = new int[init_size];
	}

	return;
}

CVector::~CVector(void)
{
	delete[] m_array;

	return;
}

CVector::CVector(const CVector& other)
{
	if(this == &other)
	{
		return ;
	}

	m_array = NULL;
	m_used  = 0;
	m_total = 0;

	if(other.m_array != NULL && other.m_total > 0)
	{
		try
		{
			m_array = new int[other.m_total];
			m_used  = other.m_used;
			m_total = other.m_total;
			memcpy(m_array, other.m_array, sizeof(int) * m_used);
		}
		catch(...)
		{
			std::cout <<"out of memory"<<std::endl;
		}
	}

	return ;
}

CVector& CVector::operator=(const CVector& other)
{
	if(this == &other)
	{
		return *this;
	}

	delete[] m_array;
	m_array = NULL;
	m_used  = 0;
	m_total = 0;

	if(other.m_array != NULL && other.m_total > 0)
	{
		try
		{
			m_array = new int[other.m_total];
			m_used  = other.m_used;
			m_total = other.m_total;
			memcpy(m_array, other.m_array, sizeof(int) * m_used);
		}
		catch(...)
		{
			std::cout <<"out of memory"<<std::endl;
		}
	}

	return *this;
}

bool CVector::extend(int delta)
{
	if((m_used + delta) < m_total)
	{
		return true;
	}

	size_t new_size = m_used + (m_used >> 1) + delta + 10;
	try
	{
		int* array = new int[new_size];
		memcpy(array, m_array, sizeof(int) * m_used);
		delete[] m_array;
		m_array = array;
		m_total = new_size;

		return true;
	}
	catch(...)
	{
		std::cout <<"out of memory"<<std::endl;
		
		return false;
	}
}

bool CVector::append(int data)
{
	return this->insert(m_used, data);
}

bool CVector::prepend(int data)
{
	return this->insert(0, data);
}

bool CVector::insert(size_t index, int data)
{
	if((index <= m_used) && this->extend(1))
	{
		int i = 0;
		for(i = m_used; i > index; i--)
		{
			m_array[i] = m_array[i-1];
		}
		m_array[index] = data;
		m_used++;

		return true;
	}
	else
	{
		return false;
	}
}

bool CVector::set(size_t index, int data)
{
	if(index < 0 || index >= m_used)
	{
		return false;
	}

	m_array[index ] = data;

	return true;
}

bool CVector::get(size_t index, int& data)
{
	if(index < 0 || index >= m_used)
	{
		return false;
	}

	data = m_array[index];

	return true;
}

#ifdef VECTOR_TEST
#include <cassert>
int main(int argc, char* argv[])
{
	int i = 0;
	int data = 0;
	CVector* dvector = new CVector(10);

	for(i = 0; i < 20; i++)
	{
		dvector->append(i);
		assert(dvector->get(i, data) && data == i);
	}

	CVector svector(*dvector);
	CVector avector = *dvector;
	
	for(i = 0; i < 20; i++)
	{
		assert(svector.get(i, data) && data == i);
	}

	delete dvector;

	return 0;
}
#endif/*VECTOR_TEST*/

