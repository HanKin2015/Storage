
/*
 * common.hpp
 * ����ͷ�ļ���,Ŀ���Ǹ�����ͷ�ļ��ṩSTL��׼��
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
#include <list>
#include "log.hpp"

using namespace std;

// ��Ҫ��extern "C"��������C++ STL���ͷ�ļ�,��<map>,<vector>�Ⱦ���template��ͷ�ļ�
// error: template with C linkage template<typename _Alloc>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif