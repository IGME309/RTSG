/*--------------------------------------------------------------------------------------------------
Made by: Alberto Bobadilla
on: 2017/06/02
--------------------------------------------------------------------------------------------------*/
#ifndef __MAIN_H_
#define __MAIN_H_
#include <iostream>
#include <deque>
#include "Alberto.h"
#define uint unsigned int
struct Foo
{
	int content = 0;
	Foo(int a_content) : content(a_content) {};
	friend std::ostream& operator<<(std::ostream& os, Foo other)
	{
		os << other.content;
		return os;
	}
};
#endif //__MAIN_H_
