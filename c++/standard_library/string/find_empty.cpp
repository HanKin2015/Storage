#include <iostream>
#include <string.h>

int main()
{
	std::string str1 = "I am hejian";
	std::string str2 = "Iamhejian";
	std::cout << std::hex << std::string::npos << std::endl;

	int index1 = str1.find("");
	int index2 = str2.find("");
	std::cout << index1 << ' ' << index2 << std::endl;
	size_t index3 = str1.find("iam");
	std::cout << index3 << std::endl;
	if (index3 == std::string::npos) {
		std::cout << "yes" << std::endl;
	}
	
	std::string str = "";
	if (str.empty()) {
		std::cout << "no" << std::endl;
	}
	return 0;
}
