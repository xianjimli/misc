#include <iostream>
#include <cstring>

template <class T>
T max(T a, T b)
{
	return a > b ? a : b ;
}

template <>
const char* max(const char* a, const char* b)
{
	return strcmp(a, b) > 0 ? a : b ;
}

int main(int argc, char* argv[])
{
	std::cout << max(100, 200) <<std::endl;
	std::cout << max(100.2, 200.1) <<std::endl;
	std::cout << max("AAA", "aaa") <<std::endl;

	return 0;
}

