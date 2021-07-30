#pragma once

#include "common.h"
#include "library/zip.h"
#include "library/unzip.h"
#include "tchar.h"

/*
* ��ѹzip�ļ���ָ���ļ��У��ļ��п��Բ����ڣ�
* 
* �и�������Ҫ������������ֵ��ļ���ѹ������ʾ����
* 
* warning C4477: ��printf��: ��ʽ�ַ�����%ws����Ҫ���͡�wchar_t *���Ĳ��������ɱ���� 1 ӵ�������͡�TCHAR *��
* warning C4477: ��printf��: ��ʽ�ַ�����%s����Ҫ���͡�char *���Ĳ��������ɱ���� 1 ӵ�������͡�TCHAR *��
* 
* ���������->�߼�->�ַ���->���ֽ�
*/
int unzip_file()
{
	HZIP hz = OpenZip(_T(R"(.\data\zip\pictures.zip)"), 0);
	ZRESULT zret = SetUnzipBaseDir(hz, _T(R"(.\data\zip\pictures\)"));	// ָ���ļ���
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
* ѹ���ļ���zip�ļ�
*/
int zip_file()
{
	HZIP hz = CreateZip(_T(R"(.\data\zip\study_zip.zip)"), 0);		// ����ѹ����λ��
	ZipAdd(hz, _T("12example.c"), _T(R"(.\data\zip\example.c)"));	// ��ѹ���ļ�����������ѹ���ļ�λ��
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

��չ�����е�һЩC++ѹ��&��ѹ��
bzip2��һ����ȫ��ѣ����ר���͸�����������ѹ����
doboz���ܹ����ٽ�ѹ����ѹ���⡣
PhysicsFS���Ը��ֹ鵵�ṩ������ʵĿ⣬��Ҫ������Ƶ��Ϸ�������в���������Quake3���ļ���ϵͳ��
KArchive�����ڴ�������д�Ͳ����ļ�����������zip�� tar���Ŀ⣬��ͨ��QIODevice��һϵ�����࣬ʹ��gzip��ʽ���ṩ��͸����ѹ���ͽ�ѹ�������ݡ�
LZ4 ���ǳ����ٵ�ѹ���㷨��
LZHAM ������ѹ�����ݿ⣬ѹ�����ʸ�LZMA�ӽ������ǽ�ѹ���ٶ�ȴҪ��öࡣ
LZMA ��7z��ʽĬ�Ϻ�ͨ�õ�ѹ��������
LZMAT ��������ٵ�ʵʱ��������ѹ���⡣
miniz����һ��CԴ�ļ�������/����ѹ���⣬ʹ��zlib����API��ZIP�鵵��д��PNGд��ʽ��
Minizip��Zlib����bug�޸���֧��PKWARE���̿�Խ��AES���ܺ�IO���塣
Snappy ������ѹ���ͽ�ѹ����
ZLib ���ǳ����յ�������ѹ���⡣
ZZIPlib���ṩZIP�鵵�Ķ�Ȩ�ޡ�
QuaZIP����ʹ�� Qt/C++ �� zlib ���м򵥷�װ������ѹ������ѹ�� ZIP �Ŀ�Դ�⣬�����ڶ���ƽ̨������Ҳ�Ƚ϶࣬���Ǳ������鷳Щ��

*/
int test_study_zip()
{
	unzip_file();
	//zip_file();
	return 0;
}