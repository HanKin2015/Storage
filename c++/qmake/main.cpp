#include <QCoreApplication>
#include <iostream>
#include "json.hpp"

int main(int argc, char *argv[]) {
	// 创建一个 JSON 对象
    nlohmann::json j;
    j["name"] = "John";
    j["age"] = 30;

    // 打印 JSON 对象
    std::cout << j.dump(4) << std::endl; // 格式化输出

    QCoreApplication a(argc, argv);
    std::cout << "Hello, Qt!" << std::endl;
    return a.exec();
}
