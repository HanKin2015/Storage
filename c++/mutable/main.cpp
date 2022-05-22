//main.cpp

#include "a.h"

#include <QApplication>

#include <iostream>

int main(int argc, char* argv[])

{
	QApplication aaa(argc, argv);

	A a(1);

	a.display();

	a.display();

	std::cout << "call func " << a.getCount() << " times." << std::endl;

	return aaa.exec();

}