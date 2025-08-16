import std;  // 以前需要include下面这一大堆东西，现在只要这一行了
//#include <iostream>
//#include <vector>
//#include <string>
//#include <string_view>

int main() {
    std::cout << "Hello Modular World!\n";

    const std::vector<std::string_view> words {"Welcome ", "Modular ", "Vector ", "With ", "auto&& "};
    for (auto&& word: words) {
        std::cout << word;
    }
    std::cout<< "\n";
}

//  clang++ -std=c++2b -Wall -Wextra -stdlib=libc++ -fmodules -fbuiltin-module-map a.cpp -o a