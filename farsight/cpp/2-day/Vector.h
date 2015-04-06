#include <iostream>

#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class CVector
{
public:
	CVector(void);
	CVector(size_t init_size);
	~CVector(void);
	CVector(const CVector& other);
	CVector& operator=(const CVector& other);

public:
	bool append(T data);
	bool prepend(T data);
	bool insert(size_t index, T data);
	bool set(size_t index, T data);
	bool get(size_t index, T& data);

private:
	bool extend(int delta);

private:
	size_t m_used;
	size_t m_total;
	T*   m_array;
};

template <class T>
CVector<T>::CVector(void)
{
	m_used  = 0;
	m_total = 0;
	m_array = NULL;

	return;
}

template <class T>
CVector<T>::CVector(size_t init_size)
{
	m_used  = 0;
	m_total = init_size;

	if(init_size > 0)
	{
		m_array = new T[init_size];
	}

	return;
}

template <class T>
CVector<T>::~CVector(void)
{
	delete[] m_array;

	return;
}

template <class T>
CVector<T>::CVector(const CVector<T>& other)
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
			m_array = new T[other.m_total];
			m_used  = other.m_used;
			m_total = other.m_total;
			for(int i = 0; i < m_used; i++)
			{
				m_array[i] = other.m_array[i];
			}
		}
		catch(...)
		{
			std::cout <<"out of memory"<<std::endl;
		}
	}

	return ;
}

template <class T>
CVector<T>& CVector<T>::operator=(const CVector<T>& other)
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
			m_array = new T[other.m_total];
			m_used  = other.m_used;
			m_total = other.m_total;
			for(int i = 0; i < m_used; i++)
			{
				m_array[i] = other.m_array[i];
			}
		}
		catch(...)
		{
			std::cout <<"out of memory"<<std::endl;
		}
	}

	return *this;
}

template <class T>
bool CVector<T>::append(T data)
{
	return this->insert(m_used, data);
}

template <class T>
bool CVector<T>::prepend(T data)
{
	return this->insert(0, data);
}

template <class T>
bool CVector<T>::insert(size_t index, T data)
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

template <class T>
bool CVector<T>::set(size_t index, T data)
{
	if(index < 0 || index >= m_used)
	{
		return false;
	}

	m_array[index ] = data;

	return true;
}

template <class T>
bool CVector<T>::get(size_t index, T& data)
{
	if(index < 0 || index >= m_used)
	{
		return false;
	}

	data = m_array[index];

	return true;
}

template <class T>
bool CVector<T>::extend(int delta)
{
	if((m_used + delta) < m_total)
	{
		return true;
	}

	size_t new_size = m_used + (m_used >> 1) + delta + 10;
	try
	{
		int i = 0;
		T* array = new T[new_size];
		for(i = 0; i < m_used; i++)
		{
			array[i] = m_array[i];
		}
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

#endif/*VECTOR_H*/
