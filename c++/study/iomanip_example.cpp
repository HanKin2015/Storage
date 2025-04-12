/*******************************************************************************
* 文 件 名: iomanip_example.cpp
* 文件描述: io代表输入输出，manip是manipulator（操纵器）的缩写
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.04.10
* 修改日期：2025.04.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>  
#include <iomanip>      
using namespace std;
int main()
{  
    double PI=3.141592654;  
    cout<<PI<<endl;  
    cout<<setprecision(2)<<PI<<endl;  
    cout<<fixed<<setprecision(2)<<PI<<endl;   
    cout<<setfill('*')<<setw(20)<<setprecision(10)<<PI<<endl;  
    cout<<setfill('*')<<setw(20)<<setprecision(10)<<left<<PI<<endl;  
    cout<<scientific<<setprecision(10)<<PI<<endl;  
    cout<<scientific<<uppercase<<setprecision(10)<<PI<<endl;    
    return 0 ;  
}  
输出结果如下：
3.14159
3.1
3.14
********3.1415926540
3.1415926540********
3.1415926540e+000
3.1415926540E+000