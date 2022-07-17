#include <iostream>
#include<string>

int main()
{
	std::string redist_path1 = "C:\Program Files (x86)\Microsoft.NET\RedistList";
	std::string redist_path2 = "C:\\Program Files (x86)\\Microsoft.NET\\RedistList";
	std::string redist_path3 = R"(C:\Program Files (x86)\Microsoft.NET\RedistList)";
	std::string redist_path4 = R"(C:\\Program Files (x86)\\Microsoft.NET\\RedistList)";

	std::cout << "redist_path1: "<< redist_path1 << std::endl;
	std::cout << "redist_path2: " << redist_path2 << std::endl;
	std::cout << "redist_path3: " << redist_path3 << std::endl;
	std::cout << "redist_path4: " << redist_path4 << std::endl;

	std::string fozu = R"(
                            _ooOoo_
                           o8888888o
                           88" . "88
                           (| -_- |)
                            O\ = /O
                        ____/`---'\____
                      .   ' \\| |// `.
                       / \\||| : |||// \
                     / _||||| -:- |||||- \
                       | | \\\ - /// | |
                     | \_| ''\---/'' | |
                      \ .-\__ `-` ___/-. /
                   ___`. .' /--.--\ `. . __
                ."" '< `.___\_<|>_/___.' >'"".
               | | : `- \`.;`\ _ /`;.`/ - ` : | |
                 \ \ `-. \_ __\ /__ _/ .-` / /
         ======`-.____`-.___\_____/___.-`____.-'======
                            `=---='
		)";

	std::cout << fozu << std::endl;

	return 0;
}