#include "MyQueue.h"
#include "Alberto.h"
#include <iostream>

int main(void)
{
	//Make first
	MyQueue<float> first;
	//Show content
	first.Print(); std::cout << std::endl;
	//Push 3 times
	first.Push(0.0f);
	first.Push(5.0f);
	first.Push(2.5f);
	//Show content
	first.Print(); std::cout << std::endl;
	
	//Pop and show
	first.Pop();
	first.Print(); std::cout << std::endl;
	//Pop and show
	first.Pop();
	first.Print(); std::cout << std::endl;
	//Pop and show (should be empty but wont break, round 1)
	first.Pop();
	first.Print(); std::cout << std::endl;
	//Pop and show (should be empty but wont break, round 2)
	first.Pop();
	first.Print(); std::cout << std::endl;

	//Push new info
	first.Push(10.0f);
	//Push 4 more times
	first.Print(); std::cout << std::endl;
	first.Push(20.0f);
	first.Push(30.0f);
	first.Push(15.0f);
	first.Push(45.0f);

	//Copy Constructor
	MyQueue<float> second(first);
	
	//Show Content of first and second
	std::cout << std::endl;
	std::cout << "First Queue" << std::endl;
	first.Print(); std::cout << std::endl;
	std::cout << "Second Queue" << std::endl;
	second.Print(); std::cout << std::endl;

	//Release twice from first
	first.Pop();
	first.Pop();
	//push to first
	first.Push(150.0f);

	//Show Content of first and second
	std::cout << std::endl;
	std::cout << "First Queue" << std::endl;
	first.Print(); std::cout << std::endl;
	std::cout << "Second Queue" << std::endl;
	second.Print(); std::cout << std::endl;

	//second is constructed but we want to copy from first, 
	//seems like a job for the Copy Assignment Operator!
	second = first;

	//Show Content of first and second
	std::cout << std::endl;
	std::cout << "First Queue" << std::endl;
	first.Print(); std::cout << std::endl;
	std::cout << "Second Queue" << std::endl;
	second.Print(); std::cout << std::endl;

	//Last we check that we can do weird but valid things like:
	first = first;
	MyQueue<float> third;
	second = third = first;

	//Show Content of first and second
	std::cout << std::endl;
	std::cout << "First Queue" << std::endl;
	first.Print(); std::cout << std::endl;
	std::cout << "Second Queue" << std::endl;
	second.Print(); std::cout << std::endl;
	std::cout << "Third Queue" << std::endl;
	third.Print(); std::cout << std::endl;


	//Make some Alberto Objects
	MyQueue<AlbertoClass> a1;
	a1.Push(AlbertoClass(45));
	a1.Push(AlbertoClass(35));
	a1.Push(AlbertoClass(25));
	MyQueue<AlbertoClass> a2(a1);
	std::cout << std::endl;
	std::cout << "Alberto Queue" << std::endl;
	a2.Print(); std::cout << std::endl;


	std::cout << std::endl;
	std::cout << "Press Enter to finish." << std::endl;
	
	getchar();
}