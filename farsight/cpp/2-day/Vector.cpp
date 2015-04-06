#include "Vector.h"
#include <cstring>
#include <cstdlib>


#ifdef VECTOR_TEST
#include <cassert>

int main(int argc, char* argv[])
{
	int i = 0;
	int data = 0;
	CVector<int>* dvector = new CVector<int>(10);

	for(i = 0; i < 20; i++)
	{
		dvector->append(i);
		assert(dvector->get(i, data) && data == i);
	}

	CVector<int> svector(*dvector);
	CVector<int> avector = *dvector;
	
	for(i = 0; i < 20; i++)
	{
		assert(svector.get(i, data) && data == i);
	}

	delete dvector;

	return 0;
}
#endif/*VECTOR_TEST*/

