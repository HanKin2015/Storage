#pragma once

#include <cstdio>
#include "library/zlib.h"

#pragma comment(lib, "library/zlib.lib")

/*
* 压缩字符串
*/
static int zlib_string()
{
	/* 原始数据 */
	unsigned char strSrc[] = "hello world! aaaaa bbbbb ccccc ddddd 中文测试 yes";
	unsigned char buf[1024] = { 0 };
	unsigned char strDst[1024] = { 0 };
	unsigned long srcLen = sizeof(strSrc);
	unsigned long bufLen = sizeof(buf);
	unsigned long dstLen = sizeof(strDst);

	printf("Src string:%s\nLength:%ld\n", strSrc, srcLen);

	/* 压缩 */
	compress(buf, &bufLen, strSrc, srcLen);
	printf("After Compressed Length:%ld\n", bufLen);

	/* 解压缩 */
	uncompress(strDst, &dstLen, buf, bufLen);
	printf("After UnCompressed Length:%ld\n", dstLen);

	printf("UnCompressed String:%s\n", strDst);
	return 0;
}

/*
* https://blog.csdn.net/wishfly/article/details/46408595
* 
* 发现zlib处理zip文件相对来说麻烦，它主要来处理gz后缀的文件
*/
static int zlib_file()
{

	return 0;
}

int test_study_zlib()
{
	zlib_string();
	return 0;
}