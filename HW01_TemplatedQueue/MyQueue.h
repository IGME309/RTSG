/*--------------------------------------------------------------------------------------------------
Made by: Alberto Bobadilla
on: 2025/01/23
--------------------------------------------------------------------------------------------------*/
#ifndef __MYQUEUE_H_
#define __MYQUEUE_H_
#include <iostream>
#define uint unsigned int
template <typename T>
class MyQueue
{
public:
	MyQueue()
	{
		
	}
	//this is missing the copy constructor and the copy assignment operator
	void Push(T input)
	{

	}
	T Pop(void)
	{
		T temp = NULL;
		return temp;
	}
	void Print(void)
	{
		std::cout << "<< PLACEHOLDER >>" << std::endl;
	}
	friend std::ostream& operator<<(std::ostream& os, MyQueue other)
	{
		os << other.content;
		return os;
	}
};

#endif //__MYQUEUE_H_
