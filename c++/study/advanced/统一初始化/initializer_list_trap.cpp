/*******************************************************************************
* 文 件 名: initializer_list_trap.cpp
* 文件描述: 场景1: std::initializer_list 的“霸道”与陷阱
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <initializer_list>

class Widget {
public:
    /**
     * @brief 构造函数1：接受两个int作为尺寸。
     * @param w 宽度。
     * @param h 高度。
     */
    Widget(int w, int h) {
        std::cout << "Calling constructor Widget(int, int) with w=" << w << ", h=" << h << std::endl;
    }

    /**
     * @brief 构造函数2：接受一个初始化列表。
     * @param list 初始化值的列表。
     * @description 这个构造函数会“劫持”花括号初始化。
     */
    Widget(std::initializer_list<int> list) {
        std::cout << "Calling constructor Widget(std::initializer_list<int>). List size is " << list.size() << std::endl;
    }
};

int main()
{
    /**
     * @brief 使用括号调用，明确匹配构造函数1。
     */
    Widget w1(5, 10); 

    /**
     * @brief 使用花括号调用，即使参数数量和类型与构造函数1完全匹配，
     *        编译器依然优先选择接受std::initializer_list的构造函数2。
     */
    Widget w2{5, 10}; 

    std::cout << "\n--- The std::vector trap ---\n" << std::endl;

    /**
     * @brief 意图：创建一个包含10个默认初始化（0）元素的vector。
     * @description 使用括号，调用了正确的构造函数 std::vector::vector(size_type count)。
     */
    std::vector<int> v_ok(10);
    std::cout << "std::vector<int> v_ok(10); -> size: " << v_ok.size() << ", content[0]: " << v_ok[0] << std::endl;

    /**
     * @brief 陷阱！意图同上，但使用了花括号。
     * @description 这匹配了接受 std::initializer_list<int> 的构造函数。
     *        结果是创建了一个只包含一个元素，其值为10的vector。
     */
    std::vector<int> v_trap{10};
    std::cout << "std::vector<int> v_trap{10}; -> size: " << v_trap.size() << ", content[0]: " << v_trap[0] << std::endl;
    
    return 0;
}