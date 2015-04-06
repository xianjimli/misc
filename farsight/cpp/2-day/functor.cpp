#include <iostream>

class Action
{
public:
	Action(int data)
	{
		std::cout<<__func__<<std::endl;
		m_data = data;
	}

	~Action(void)
	{
		std::cout<<__func__<<std::endl;
	}

public:
	void operator()()
	{
		std::cout<<m_data<<std::endl;	
	}
private:
	int m_data;
};

template <class T> void do_sth(T& action)
{
	action();

	return;
}

int main(int argc, char* argv[])
{
	Action action(100);

	do_sth(action);

	return 0;
}
