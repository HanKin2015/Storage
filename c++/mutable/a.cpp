//a.cpp   

#include <iostream>

void A::display() const

{
    ++m_nCount;

    std::cout << " call func display()" << "\n";

}

 

int A::getCount() const

{
    return m_nCount;

}