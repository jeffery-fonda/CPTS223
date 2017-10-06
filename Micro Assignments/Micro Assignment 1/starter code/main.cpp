#include <iostream>
#include <cstdlib>
#include "ADTs\Array.h"
#include "ADTs\Vector.h"
#include "ADTs\Indexed.h"
#include "ADTs\LinkedList.h"

using namespace std;

void arrayTest()
{
	//base array initialization test
	cout << "Test #1: Basic array behavior" << endl;
	Array<int> numbers(10);
	for (int i = 1; i < 11; i++)
	{
		numbers.addElement(i);
	}
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5 6 7 8 9 10" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < numbers.getSize(); i++)
	{
		cout << numbers.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use copy constructor
	cout << "Test #2: Copy constructor behavior" << endl;
	Array<int> copy1{ numbers };
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5 6 7 8 9 10" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < copy1.getSize(); i++)
	{
		cout << copy1.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use move constructor
	cout << "Test #3: Move constructor behavior" << endl;
	Array<int> moved1{ Array<int>{1, 2, 3, 4, 5} };
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < moved1.getSize(); i++)
	{
		cout << moved1.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use copy operator
	cout << "Test #4: Copy operator behavior" << endl;
	copy1 = moved1;
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < copy1.getSize(); i++)
	{
		cout << copy1.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use move operator
	cout << "Test #5: Move constructor behavior" << endl;
	moved1 = Array<int>{ 6, 7, 8, 9, 10 };
	cout << "Result:" << endl;
	cout << "Expected:\t6 7 8 9 10" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < moved1.getSize(); i++)
	{
		cout << moved1.getElementAt(i) << " ";
	}
	cout << endl << endl;

}

void vectorTest()
{
	//base array initialization test
	cout << "Test #1: Basic vector behavior" << endl;
	Vector<int> numbers(10);
	for (int i = 1; i < 11; i++)
	{
		numbers.addElement(i);
	}
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5 6 7 8 9 10" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < numbers.getSize(); i++)
	{
		cout << numbers.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use copy constructor
	cout << "Test #2: Copy constructor behavior" << endl;
	Vector<int> copy1{ numbers };
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5 6 7 8 9 10" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < copy1.getSize(); i++)
	{
		cout << copy1.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use move constructor
	cout << "Test #3: Move constructor behavior" << endl;
	Vector<int> moved1{ Vector<int>{1, 2, 3, 4, 5} };
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < moved1.getSize(); i++)
	{
		cout << moved1.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use copy operator
	cout << "Test #4: Copy operator behavior" << endl;
	copy1 = moved1;
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < copy1.getSize(); i++)
	{
		cout << copy1.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use move operator
	cout << "Test #5: Move constructor behavior" << endl;
	moved1 = Vector<int>{ 6, 7, 8, 9, 10 };
	cout << "Result:" << endl;
	cout << "Expected:\t6 7 8 9 10" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < moved1.getSize(); i++)
	{
		cout << moved1.getElementAt(i) << " ";
	}
	cout << endl << endl;
}

void linkedListTest()
{
	//base array initialization test
	cout << "Test #1: Basic Linked List behavior" << endl;
	LinkedList<int> numbers{};
	for (int i = 1; i < 11; i++)
	{
		numbers.addElement(i);
	}
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5 6 7 8 9 10" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < numbers.getSize(); i++)
	{
		cout << numbers.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use copy constructor
	cout << "Test #2: Copy constructor behavior" << endl;
	LinkedList<int> copy1{ numbers };
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5 6 7 8 9 10" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < copy1.getSize(); i++)
	{
		cout << copy1.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use move constructor
	cout << "Test #3: Move constructor behavior" << endl;
	LinkedList<int> moved1{ LinkedList<int>{1, 2, 3, 4, 5} };
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < moved1.getSize(); i++)
	{
		cout << moved1.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use copy operator
	cout << "Test #4: Copy operator behavior" << endl;
	copy1 = moved1;
	cout << "Result:" << endl;
	cout << "Expected:\t1 2 3 4 5" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < copy1.getSize(); i++)
	{
		cout << copy1.getElementAt(i) << " ";
	}
	cout << endl << endl;

	//use move operator
	cout << "Test #5: Move constructor behavior" << endl;
	moved1 = LinkedList<int>{ 6, 7, 8, 9, 10 };
	cout << "Result:" << endl;
	cout << "Expected:\t6 7 8 9 10" << endl;
	cout << "Actual:\t\t";
	for (int i = 0; i < moved1.getSize(); i++)
	{
		cout << moved1.getElementAt(i) << " ";
	}
	cout << endl << endl;
}

int main(int argc, char *argv[])
{
	arrayTest();
	vectorTest();
	linkedListTest();
}