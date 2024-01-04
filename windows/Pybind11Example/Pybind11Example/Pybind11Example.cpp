// Pybind11Example.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <pybind11/pybind11.h>
#include <iostream>

// 普通函数
void age(double age) {
	std::cout << "age = " << age << std::endl;
}

std::string Name(std::string& name) {
	std::cout << "Name: " << name << std::endl;
	return name;
}

// 类
class Hello
{
public:
	Hello() {}
	void say(const std::string s) {
		std::cout << s << std::endl;
	}
};

// 命名空间中的类
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

// 带参数的构造函数
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

// 结构体
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

// 注意这里的example1是python导入包的名字命名，而不是导入该vs项目的名称，除非命名一样( 模块名, 模块实例对象 )
PYBIND11_MODULE(Pybind11Example, m)
{
	m.doc() = "pybind11 example";	// 可选，说明这个模块是做什么的
	m.def("age", &age);
	m.def("Name", &Name);

	pybind11::class_<Hello>(m, "Hello")
		.def(pybind11::init())
		.def("say", &Hello::say);

	pybind11::class_<NS::World>(m, "World")
		.def(pybind11::init())
		.def("say", &NS::World::say);

	// py::dynamic_attr()为C++类启用动态属性
	pybind11::class_<Test>(m, "Test", py::dynamic_attr())	// 封装类
		.def(pybind11::init< int, int, std::string, int >())// 构造器的模版参数列表中需要按照构造函数的参数类型填入才能调用对应的参数
		.def("print", &Test::Print)			// python调用的时候使用print而不是Print
		.def_readwrite("name", &Test::name)	// 访问类中公有变量
		.def("GetName", &Test::GetName)
		.def_property("age", &Test::GetAge, &Test::SetAge)	// 访问类中私有变量，注意GetAge和SetAge函数顺序不能反
		.def("GetHeight", &Test::GetHeight) // 上面方法可以直接通过变量赋值方式进行修改，这种方法则是函数调用方式
		.def("SetHeight", &Test::SetHeight);

	pybind11::class_<ST>(m, "ST")
		.def(pybind11::init<std::string>())
		.def("SetName", &ST::SetName)
		.def_readwrite("str", &ST::str)
		.def_readonly("name", &ST::name)
		.def_readwrite("i", &ST::i);
}

