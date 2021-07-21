﻿#pragma once

#include <cstdio>
#include "zlib.h"

#pragma comment(lib, "zlib.lib")

void zlib_string()
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

	return;
}

int test_study_zlib()
{
	zlib_string();
	return 0;
}