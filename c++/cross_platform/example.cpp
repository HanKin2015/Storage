#if defined(_MSC_VER) && (_MSC_VER < 1800)  // Visual Studio 2013 以下版本
// c++使用inttypes.h，需要定义该宏，使其生效
#define __STDC_FORMAT_MACROS

#include "utils/msinttypes/stdint.h"
#include "utils/msinttypes/inttypes.h"
#else
// Other compilers should have this.
#include <stdint.h>
#include <inttypes.h>
#endif

/**
 * @brief 如果后续要兼容windows下的usbip，需要此定义，来容纳下windows的socekt的类型的大小
 *        - Windows下实际上socket_t就是个地址
 *        - Linux下是int类型
 * @ref 该定义参考自libevent的evutil_socket_t
 * @remark 原说明如下
 * A type wide enough to hold the output of "socket()" or "accept()".  On
 * Windows, this is an intptr_t; elsewhere, it is an int. */
#ifdef _WIN32
#define usbip_socket_t intptr_t
#else
#define usbip_socket_t int
#endif

#ifdef _WIN64
#define PRIfd   PRIi64
#else // WIN32, Linux   socket_t = int
#define PRIfd   "d"
#endif








