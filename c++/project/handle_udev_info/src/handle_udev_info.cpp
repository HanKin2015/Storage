/**
 * �� �� ��: handle_udev_info.cpp
 * �ļ�����: ����ѹ�������ռ���������Ϣ
 * ��    ��: HJ
 * ��������: 2021.05.25
 * �޸����ڣ�2021.05.25
 *
 * Copyright (c) 2021 HJ. All rights reserved.
 */

#include "handle_udev_info.h"

/**
 * @brief �������ݵ�����csv�ļ�
 * @note
 * @param udev_data [in] USB�豸��Ϣ����
 * @return ��
 */
static int get_file_path(string dir_path, vector<string> &files_path)
{
    DIR *dir;
    struct dirent *dir_info;
    struct stat stat_buf;
    string new_dir_path;
    lstat(dir_path.c_str(), &stat_buf);
 
    if (S_ISREG(stat_buf.st_mode)) {
        files_path.push_back(dir_path);
    } else if (S_ISDIR(stat_buf.st_mode)) {
        if ((dir = opendir(dir_path.c_str())) == NULL) {
            perror("opendir");
            return -1;
        }   
 
        while ((dir_info = readdir(dir)) != NULL) {
            if (strcmp(dir_info->d_name, ".") == 0 || strcmp(dir_info->d_name, "..") == 0) continue;
            new_dir_path = dir_path + "/" + dir_info->d_name;
            get_file_path(new_dir_path, files_path);
        }
        closedir(dir);
    } else {
        perror("unkonow");
        return -2;
    }
    return 0;
}

/**
 * @brief �������ݵ�����csv�ļ�
 * @note
 * @param udev_data [in] USB�豸��Ϣ����
 * @return ��
 */
static int SaveData2Csv(vector<udev_info> udev_data)
{
    LOGI("start to save data to local csv file [%s].", CSV_FILE_PATH);

    FILE* fp = fopen(CSV_FILE_PATH, "w");
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

int handle_udev_main()
{
    int ret = 0;
    string cmd = "";
    vector <string> files_path;
    Trie* udev_tree = nullptr;
    string pvid = "";
    vector<JSON_DATA_STRUCT> json_data;
    cJSON* json_obj = nullptr;

    // 1.��ѹ���ļ���data�ļ�����
    ret = unzip_file(DATA_FILE_PATH, JSON_DATA_DIR);
    if (ret != 0) {
        LOGE("unzip_file failed [%d]", ret);
        goto FAILED;
    }

    // 2.����json�ļ�
    get_file_path(JSON_DATA_DIR, files_path);
    LOGI("files_path size [%lld]", files_path.size());
    for (string file_path : files_path) {
        json_obj = get_json_obj(file_path.c_str());
        get_json_data(json_obj, json_data);
    }
    LOGI("untreated json data size [%lld].", json_data.size());

    // 4���ֵ����洢
    udev_tree = new Trie();
    for (JSON_DATA_STRUCT udev_data : json_data) {
        pvid = udev_data.vid + udev_data.pid;
        // ת��ΪСд��ĸ��ǰ��������˴������ʡ��
        //transform(pvid.begin(), pvid.end(), pvid.begin(), ::tolower);
        udev_tree->insert(pvid, udev_data);
    }

    // 5������ȥ��������ṹ����
    json_data.clear();
    udev_tree->output(udev_tree->root, json_data);
    LOGI("treated json data size [%lld].", json_data.size());

    // 5���������ݵ�����csv����ļ���
    ret = SaveData2Csv(json_data);
    if (ret != 0) {
        LOGE("SaveData2Csv failed [%d]", ret);
        goto FAILED;
    }

    // 6.ɾ���м䴴�����ļ����ļ���
    return 0;

FAILED:
    LOGE("handle usb device info failed.");
    return -1;
}
