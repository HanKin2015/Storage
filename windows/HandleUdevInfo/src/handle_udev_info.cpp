/*
 * handle_udev_info.cpp
 * ����ѹ�������ռ���������Ϣ
 * 
 * 1.��ѹ����ȡ��ÿ��json�ļ�
 * 
 * date  : 2021.05.25
 * author: hejian
 * 
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#include "handle_udev_info.hpp"

/*
 * @brief �ж��ļ�����Ŀ¼�Ƿ����
 * @note
 * 
 * @param path [in] �ļ�����Ŀ¼·��
 * @return ���ڷ���true����֮false
 */
static bool IsExist(string path)
{
    return (_access(path.c_str(), F_OK) != -1);
}

/*
 * @brief ��ѹzip�ļ���Ŀ���ļ���
 * @note  ʹ��7z.exe���߽�ѹ
 * 
 * @param path [in] �����ļ���·��
 * @param target_dir [in] Ŀ���ļ���·��
 * @return ��
 */
void UnzipFileBy7z(vector<string> files_path, string target_dir)
{
    for (string file_path : files_path) {
        // ��ȡ�ļ���׺
        size_t idx = file_path.find_last_of('.');
        string postfix = file_path.substr(idx + 1);
        if (postfix == "zip") {
            // ��zipѹ���ļ���Ŀ���ļ���
            string cmd = ".\\tools\\7zx64.exe x -y " + file_path + " -o" + target_dir;
            system(cmd.c_str());
        }
    }
    return ;
}

/*
 * @brief string����תtchar����
 * @note ����ͨ�������ַ���Ϊʹ�ö��ֽ��ַ�����ת��
 * 
 * @param src [in] string�ַ���
 * @param buf [out] tchar�ַ���
 * @return ��
 */
static void string2tchar(std::string& src, TCHAR* buf)
{
#ifdef _UNICODE  
    _stprintf_s(buf, MAX_PATH, _T("%S"), src.c_str());  // %S���ַ�  
#else  
    _stprintf_s(buf, MAX_PATH, _T("%s"), src.c_str());  // %s���ַ�
#endif
    return;
}

/*
 * @brief ��ѹzip�ļ���Ŀ���ļ���
 * @note  ʹ��Zip Utils��
 *
 * @param path [in] �����ļ�·��
 * @param target_dir [in] Ŀ���ļ���·��
 * @return ��
 */
static int UnzipFile(string file_path, string target_dir)
{
    // ��ȡ�ļ���׺
    size_t idx = file_path.find_last_of('.');
    string postfix = file_path.substr(idx + 1);
    if (postfix == "zip") {
        // ��zipѹ���ļ���Ŀ���ļ���
        HZIP hz = OpenZip(file_path.c_str(), nullptr);
        if (!hz) {
            LOGE("OpenZip failed.");
            return -1;
        }
        ZRESULT zret = SetUnzipBaseDir(hz, target_dir.c_str());	// ָ���ļ���
        if (zret != ZR_OK) {
            LOGE("SetUnzipBaseDir failed, 0x%x.", zret);
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
    }
    return 0;
}

/*
 * @brief ��ѹzip�ļ���Ŀ���ļ���
 * @note  ʹ��Zip Utils�⣨���̰߳汾��
 * 
 * @param path [in] �����ļ���·��
 * @param target_dir [in] Ŀ���ļ���·��
 * @return ��
 */
int UnzipFileSinglethread(vector<string> files_path, string target_dir)
{
    for (string file_path : files_path) {
        UnzipFile(file_path, target_dir);
    }
    return 0;
}

/*
 * @brief ��ѹzip�ļ���Ŀ���ļ���
 * @note  ʹ��Zip Utils�⣨���̰߳汾��
 * 
 * @param path [in] �����ļ���·��
 * @param target_dir [in] Ŀ���ļ���·��
 * @return ��
 */
int UnzipFileMultithread(vector<string> files_path, string target_dir)
{
    list<thread> threads;

    for (string file_path : files_path) {
        threads.push_back(thread(UnzipFile, file_path, target_dir));
    }
    for (thread& t : threads) {
        t.join();
    }
    return 0;
}

/*
 * @brief ��ȡdir_path�ļ����������ļ������·��
 * @note
 * @param dir_path [in] �����ļ���·��
 * @param files_path [out] �ļ������·��
 * @return ��
 */
int GetFileRelaPath(string dir_path, vector<string> &files_path)
{
    intptr_t hFile = 0;             // �ļ����
    struct _finddata_t file_info;   // �ļ���Ϣ
    string path;

    if ((hFile = _findfirst(path.assign(dir_path).append("\\*").c_str(), &file_info)) != -1) {
        do {
            string file_path = path.assign(dir_path).append("\\").append(file_info.name);
            // �����Ŀ¼,����֮,�������,�����б�
            if ((file_info.attrib & _A_SUBDIR)) {
                if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0) {
                    GetFileRelaPath(file_path, files_path);
                }
            } else {
                LOGD("%s", file_path.c_str());
                files_path.push_back(file_path);
            }
        } while (_findnext(hFile, &file_info) == 0);
        _findclose(hFile);
    } else {
        LOGE("dir_path is not exist.");
        return -1;
    }
    return 0;
}

/*
 * @brief �������ݵ�����csv�ļ�
 * @note
 * @param udev_data [in] USB�豸��Ϣ����
 * @return ��
 */
static int SaveData2Csv(vector<udev_info> udev_data)
{
    LOGI("start to save data to local csv file [%s].", CSV_FILE_PATH.c_str());

    FILE* fp = fopen(CSV_FILE_PATH.c_str(), "w");
    if (!fp) {
        LOGE("open CSV_FILE_PATH failed! strerror: %s", strerror(errno));
        return -1;
    }
    for (udev_info& it : udev_data) {
        fprintf(fp, "%s,%s,%s,%s,%s\n", it.vid.c_str(), it.pid.c_str(), \
            it.rev.c_str(), it.man_str.c_str(), it.pro_str.c_str());
    }
    fclose(fp);
    return 0;
}

/*
 * @brief ɾ��һ���ļ����µ���������
 * @note
 * @param dir_path [in] �ļ���·��
 * @return ��
 */
int DeleteDirectory(string dir_path)
{
    LOGD("start delete directory [%s].", dir_path.c_str());

    intptr_t hFile = 0;             // �ļ����
    struct _finddata_t file_info;   // �ļ���Ϣ
    string path;

    if ((hFile = _findfirst(path.assign(dir_path).append("\\*").c_str(), &file_info)) != -1) {
        do {
            string file_path = path.assign(dir_path).append("\\").append(file_info.name);
            // �����Ŀ¼,����֮,�������,�����б�
            if ((file_info.attrib & _A_SUBDIR)) {
                if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0) {
                    DeleteDirectory(file_path);             //�ݹ�ɾ���ļ���
                    RemoveDirectory(file_path.c_str());     //ֻ��ɾ���յ��ļ���
                }
            } else {
                LOGD("delete file [%s].", file_path.c_str());
                DeleteFile(file_path.c_str());
            }
        } while (_findnext(hFile, &file_info) == 0);
        _findclose(hFile);
    } else {
        LOGE("dir_path is not exist.");
        return -1;
    }
    RemoveDirectory(dir_path.c_str());
    return 0;
}

int handle_udev_main()
{
    int ret = 0;
    string cmd = "";
    vector <string> files_path;
    Trie* udev_tree = nullptr;
    string pvid = "";
    vector<JSON_DATA_STRUCT> json_data;
    cJSON* json_obj = nullptr;

    // 1.��ѹ���ļ���temp�ļ���
    ret = UnzipFile(DATA_FILE_PATH, TEMP_DIR);
    if (ret != 0) {
        goto FAILED;
    }

    // 2.��ȡjson�ļ���������data�ļ�����
    ret = GetFileRelaPath(TEMP_DIR, files_path);
    if (ret != 0) {
        goto FAILED;
    }
    LOGI("zip file's relative path size [%I64d].", files_path.size());
    //ret = UnzipFileSinglethread(files_path, JSON_DATA_DIR);
    ret = UnzipFileMultithread(files_path, JSON_DATA_DIR);
    if (ret != 0) {
        goto FAILED;
    }

    // 3.����json�ļ�
    files_path.clear();
    GetFileRelaPath(JSON_DATA_DIR, files_path);
    for (string file_path : files_path) {
        json_obj = GetJsonObject(file_path.c_str());
        GetJsonData(json_obj, json_data);
    }
    LOGI("untreated json data size [%I64d].", json_data.size());

    // 4���ֵ����洢
    udev_tree = new Trie();
    for (JSON_DATA_STRUCT udev_data : json_data) {
        pvid = udev_data.vid + udev_data.pid;
        // ת��ΪСд��ĸ��ǰ��������˴������ʡ��
        //transform(pvid.begin(), pvid.end(), pvid.begin(), ::tolower);
        udev_tree->Insert(pvid, udev_data);
    }

    // 5������ȥ��������ṹ����
    json_data.clear();
    udev_tree->SortOutput(udev_tree->root, json_data);
    LOGI("treated json data size [%I64d].", json_data.size());

    // 5���������ݵ�����csv����ļ���
    ret = SaveData2Csv(json_data);
    if (ret != 0) {
        goto FAILED;
    }

    // 6.ɾ���м䴴�����ļ����ļ���
    DeleteDirectory(TEMP_DIR);
    DeleteDirectory(JSON_DATA_DIR);
    return 0;

FAILED:
    LOGE("handle usb device info failed.");
    return -1;
}
