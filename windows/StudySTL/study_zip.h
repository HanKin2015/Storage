#pragma once

#include "common.h"
#include "library/zip.h"
#include "library/unzip.h"
#include "tchar.h"

/*
* 解压zip文件到指定文件夹（文件夹可以不存在）
* 
* 有个问题需要解决，中文名字的文件解压出来显示乱码
* 
* warning C4477: “printf”: 格式字符串“%ws”需要类型“wchar_t *”的参数，但可变参数 1 拥有了类型“TCHAR *”
* warning C4477: “printf”: 格式字符串“%s”需要类型“char *”的参数，但可变参数 1 拥有了类型“TCHAR *”
* 
* 解决：属性->高级->字符集->多字节
*/
int unzip_file()
{
	HZIP hz = OpenZip(_T(R"(.\data\zip\pictures.zip)"), 0);
	ZRESULT zret = SetUnzipBaseDir(hz, _T(R"(.\data\zip\pictures\)"));	// 指定文件夹
	if (zret != ZR_OK) {
		printf("SetUnzipBaseDir failed, %x.\n", zret);
		return -1;
	}

	ZIPENTRY ze;
	GetZipItem(hz, -1, &ze);
	int numitems = ze.index;
	for (int i = 0; i < numitems; i++) {
		GetZipItem(hz, i, &ze);
		UnzipItem(hz, i, ze.name);
	}
	CloseZip(hz);
	return 0;
}

/*
* 压缩文件到zip文件
*/
int zip_file()
{
	HZIP hz = CreateZip(_T(R"(.\data\zip\study_zip.zip)"), 0);		// 最终压缩包位置
	ZipAdd(hz, _T("12example.c"), _T(R"(.\data\zip\example.c)"));	// 被压缩文件重命名，被压缩文件位置
	ZipAdd(hz, _T("readme.txt"), _T(R"(.\data\zip\readme.txt)"));
	ZipAdd(hz, _T("mouse.png"), _T(R"(.\data\zip\mouse.png)"));
	ZipAdd(hz, _T("zip.h"), _T(R"(.\data\zip\zip.h)"));
	CloseZip(hz);
	return 0;
}

/*
* https://www.cnblogs.com/linuxAndMcu/p/14508503.html
* http://www.wischik.com/lu/programmer/zip_utils.html
* 

扩展：流行的一些C++压缩&解压库
bzip2：一个完全免费，免费专利和高质量的数据压缩。
doboz：能够快速解压缩的压缩库。
PhysicsFS：对各种归档提供抽象访问的库，主要用于视频游戏，设计灵感部分来自于Quake3的文件子系统。
KArchive：用于创建，读写和操作文件档案（例如zip和 tar）的库，它通过QIODevice的一系列子类，使用gzip格式，提供了透明的压缩和解压缩的数据。
LZ4 ：非常快速的压缩算法。
LZHAM ：无损压缩数据库，压缩比率跟LZMA接近，但是解压缩速度却要快得多。
LZMA ：7z格式默认和通用的压缩方法。
LZMAT ：及其快速的实时无损数据压缩库。
miniz：单一的C源文件，紧缩/膨胀压缩库，使用zlib兼容API，ZIP归档读写，PNG写方式。
Minizip：Zlib最新bug修复，支持PKWARE磁盘跨越，AES加密和IO缓冲。
Snappy ：快速压缩和解压缩。
ZLib ：非常紧凑的数据流压缩库。
ZZIPlib：提供ZIP归档的读权限。
QuaZIP：是使用 Qt/C++ 对 zlib 进行简单封装的用于压缩及解压缩 ZIP 的开源库，适用于多种平台，资料也比较多，就是编译稍麻烦些。

*/
int test_study_zip()
{
	unzip_file();
	//zip_file();
	return 0;
}