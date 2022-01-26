//a.h

class A

{
public:

	A(int a): m_na(a), m_nCount(0){}

	~A(){}

	void display() const;

	int getCount() const;

private:

	int m_na;

	mutable int m_nCount;

};