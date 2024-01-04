// Pybind11Example.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include <pybind11/pybind11.h>
#include <iostream>

// ��ͨ����
void age(double age) {
	std::cout << "age = " << age << std::endl;
}

std::string Name(std::string& name) {
	std::cout << "Name: " << name << std::endl;
	return name;
}

// ��
class Hello
{
public:
	Hello() {}
	void say(const std::string s) {
		std::cout << s << std::endl;
	}
};

// �����ռ��е���
namespace NS
{
	class World
	{
	public:
		World() {}
		void say(const std::string s) {
			std::cout << s << std::endl;
		}
	};
}

// �������Ĺ��캯��
class Test {
public:
	Test(int i, int j, std::string name, int age)
		:mI(i), mJ(j), name(name), age(age) {

	}

	void Print() {
		std::cout << "i= " << mI << " j= " << mJ << std::endl;
	}

	std::string GetName() {
		return name;
	}

	void SetAge(int a) {
		age = a;
	}

	int GetAge() {
		return age;
	}

	void SetHeight(int h) {
		height = h;
	}

	int GetHeight() {
		return height;
	}

private:
	int mI;
	int mJ;
	int age;
	int height;

public:
	std::string name;
};

// �ṹ��
struct ST {
	std::string str;
	uint64_t i;
	std::string name;
	ST(std::string name) {
		this->name = name;
	}
	void SetName(std::string name) {
		this->name = name;
	}
};

namespace py = pybind11;

// ע�������example1��python����������������������ǵ����vs��Ŀ�����ƣ���������һ��( ģ����, ģ��ʵ������ )
PYBIND11_MODULE(Pybind11Example, m)
{
	m.doc() = "pybind11 example";	// ��ѡ��˵�����ģ������ʲô��
	m.def("age", &age);
	m.def("Name", &Name);

	pybind11::class_<Hello>(m, "Hello")
		.def(pybind11::init())
		.def("say", &Hello::say);

	pybind11::class_<NS::World>(m, "World")
		.def(pybind11::init())
		.def("say", &NS::World::say);

	// py::dynamic_attr()ΪC++�����ö�̬����
	pybind11::class_<Test>(m, "Test", py::dynamic_attr())	// ��װ��
		.def(pybind11::init< int, int, std::string, int >())// ��������ģ������б�����Ҫ���չ��캯���Ĳ�������������ܵ��ö�Ӧ�Ĳ���
		.def("print", &Test::Print)			// python���õ�ʱ��ʹ��print������Print
		.def_readwrite("name", &Test::name)	// �������й��б���
		.def("GetName", &Test::GetName)
		.def_property("age", &Test::GetAge, &Test::SetAge)	// ��������˽�б�����ע��GetAge��SetAge����˳���ܷ�
		.def("GetHeight", &Test::GetHeight) // ���淽������ֱ��ͨ��������ֵ��ʽ�����޸ģ����ַ������Ǻ������÷�ʽ
		.def("SetHeight", &Test::SetHeight);

	pybind11::class_<ST>(m, "ST")
		.def(pybind11::init<std::string>())
		.def("SetName", &ST::SetName)
		.def_readwrite("str", &ST::str)
		.def_readonly("name", &ST::name)
		.def_readwrite("i", &ST::i);
}

