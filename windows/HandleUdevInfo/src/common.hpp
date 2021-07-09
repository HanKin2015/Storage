
/*
 * common.hpp
 * 公共头文件库,目的是给其他头文件提供STL标准库
 *  
 * date  : 2021.06.25
 * author: hejian
 * 
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <ctime>
#include <cstdlib>
#include <direct.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <cmath>
#include <map>
#include <algorithm>
#include <windows.h>
#include <stdint.h>
#include <windowsx.h>
#include <sys\timeb.h>

using namespace std;

// 不要在extern "C"的中引用C++ STL库的头文件,如<map>,<vector>等具有template的头文件
// error: template with C linkage template<typename _Alloc>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif