/*******************************************************************************
* 文 件 名: raw_string_literals.cpp
* 文件描述: 原始字符串字面量
* 备    注: 由R"delim(raw_characters)delim"的语法表示，其中delim可以是任何非空字符序列，并且在开始和结束位置上必须匹配
* 作    者: HanKin
* 创建日期: 2024.02.02
* 修改日期：2024.02.02
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
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
    
    const char* str2 = R"###(This is a "quoted" string.)###";
    std::cout << str2 << std::endl;  // 输出：This is a "quoted" string.const char* str2 = R"###(This is a "quoted" string.)###";
    std::cout << str2 << std::endl;  // 输出：This is a "quoted" string.

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