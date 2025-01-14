#include "Main.h"
template <typename T> 
void Print(std::deque<T> a_queue)
{
	std::cout << "Begining of queue......." << std::endl;
	uint count = a_queue.size();
	for (uint i = 0; i < count; ++i)
	{
		std::cout << a_queue[i];
		std::cout << std::endl;
	}
	std::cout << "End of queue............" << std::endl;
}

int main(void)
{
	std::deque<int> myQueue;
	//Push elements
	myQueue.push_back(0);
	std::cout << "	just pushed +++++" << std::endl;
	myQueue.push_back(1);
	std::cout << "	just pushed +++++" << std::endl;
	myQueue.push_back(2);
	std::cout << "	just pushed +++++" << std::endl;
	//Print queue
	Print<int>(myQueue);
	//pop an element
	myQueue.pop_front();
	std::cout << "		just popped -----" << std::endl;
	//add elements
	myQueue.push_back(3);
	std::cout << "	just pushed +++++" << std::endl;
	myQueue.push_back(4);
	std::cout << "	just pushed +++++" << std::endl;
	myQueue.push_back(5);
	std::cout << "	just pushed +++++" << std::endl;
	//Print queue
	Print<int>(myQueue);
	myQueue.pop_front();
	std::cout << "		just popped -----" << std::endl;
	myQueue.pop_front();
	std::cout << "		just popped -----" << std::endl;
	//Print queue
	Print<int>(myQueue);
	//clear queue
	uint count = myQueue.size();
	for (uint i = 0; i < count; ++i)
	{
		myQueue.pop_front();
		std::cout << "		just popped -----" << std::endl;
	}
	//Print queue
	Print<int>(myQueue);

	//Complex Data usage
	std::deque<Foo> myFooQueue;
	for (uint i = 0; i < 10; ++i)
	{
		Foo foo(i);
		myFooQueue.push_back(foo);
		std::cout << "	just pushed +++++" << std::endl;
		if (i % 2 == 0)
		{
			myFooQueue.pop_front();
			std::cout << "		just popped -----" << std::endl;
		}
	}

	std::deque<AlbertoClass> myAlbertoQueue;
	for (uint i = 30; i < 40; ++i)
	{
		AlbertoClass alberto(i);
		myAlbertoQueue.push_back(alberto);
		std::cout << "	just pushed +++++" << std::endl;
	}
	std::cout << "	Content" << std::endl;
	for (uint i = 0; i < 10; ++i)
	{
		std::cout << myAlbertoQueue[i] << std::endl;
	}

	std::cout << "Press Enter to finish." << std::endl;


	
	getchar();
}