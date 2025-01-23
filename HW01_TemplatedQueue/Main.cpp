#include "MyQueue.h"
#include "Alberto.h"
#include <iostream>

int main(void)
{
	//Make first
	std::cout << "Making first" << std::endl;
	MyQueue<float> first;
	//Show content
	std::cout << "Showing content of first" << std::endl;
	first.Print(); std::cout << std::endl;
	//Push 3 times
	std::cout << "Pushing 3 times to first (0,5,2.5)" << std::endl;
	first.Push(0.0f);
	first.Push(5.0f);
	first.Push(2.5f);
	//Show content
	std::cout << "Showing content of first (0,2.5,5)" << std::endl;
	first.Print(); std::cout << std::endl;
	
	//Pop and show
	std::cout << "Popping from first" << std::endl;
	first.Pop();
	std::cout << "Showing content of first (2.5, 5)" << std::endl;
	first.Print(); std::cout << std::endl;
	//Pop and show
	std::cout << "Popping from first" << std::endl;
	first.Pop();
	std::cout << "Showing content of first (5)" << std::endl;
	first.Print(); std::cout << std::endl;
	//Pop and show (should be empty but wont break, round 1)
	first.Pop();
	std::cout << "Popping from first (only one element left)" << std::endl;
	std::cout << "Showing content of first ()" << std::endl;
	first.Print(); std::cout << std::endl;
	//Pop and show (should be empty but wont break, round 2)
	std::cout << "Popping from first (its empty at this point)" << std::endl;
	first.Pop();
	std::cout << "Showing content of first ()" << std::endl;
	first.Print(); std::cout << std::endl;

	//Push new info
	std::cout << "Pushing to first (10)" << std::endl;
	first.Push(10.0f);
	std::cout << "Showing content of first (10)" << std::endl;
	//Push 4 more times
	first.Print(); std::cout << std::endl;
	std::cout << "Pushing to first 4 times (20,30,15,45)" << std::endl;
	first.Push(20.0f);
	first.Push(30.0f);
	first.Push(15.0f);
	first.Push(45.0f);

	//Copy Constructor
	std::cout << "Copying from first to construct second" << std::endl;
	MyQueue<float> second(first);
	//Show Content of first and second
	std::cout << std::endl;
	std::cout << "First Queue" << std::endl;
	first.Print(); std::cout << std::endl;
	std::cout << "Second Queue" << std::endl;
	second.Print(); std::cout << std::endl;

	//Pop twice from first
	std::cout << "Pop twice from first" << std::endl;
	first.Pop();
	first.Pop();
	//push to first
	std::cout << "Push to first (150)" << std::endl;
	first.Push(150.0f);

	//Show Content of first and second
	std::cout << std::endl;
	std::cout << "First Queue" << std::endl;
	first.Print(); std::cout << std::endl;
	std::cout << "Second Queue" << std::endl;
	second.Print(); std::cout << std::endl;

	//second is constructed but we want to copy from first, 
	//seems like a job for the Copy Assignment Operator!
	std::cout << "Overriding content of second with first's" << std::endl;
	second = first;

	//Show Content of first and second
	std::cout << std::endl;
	std::cout << "First Queue" << std::endl;
	first.Print(); std::cout << std::endl;
	std::cout << "Second Queue" << std::endl;
	second.Print(); std::cout << std::endl;

	//Last we check that we can do weird but valid things like:
	std::cout << "Overriding content of first with first's" << std::endl;
	first = first;
	MyQueue<float> third;
	std::cout << "Copy assignment and copy constructor in one line" << std::endl;
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
	std::cout << "Make an Alberto queue and push 3 times to it" << std::endl;
	MyQueue<AlbertoClass> a1;
	a1.Push(AlbertoClass(45));
	a1.Push(AlbertoClass(35));
	a1.Push(AlbertoClass(25));
	std::cout << "Make an new Alberto2 and copy Alberto's content" << std::endl;
	MyQueue<AlbertoClass> a2(a1);
	std::cout << std::endl;
	std::cout << "Alberto2 Queue" << std::endl;
	a2.Print(); std::cout << std::endl;


	std::cout << std::endl;
	std::cout << "Press Enter to finish." << std::endl;
	
	getchar();
}