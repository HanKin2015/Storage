import os
import shutil

path = 'D:/Users/Administrator/My Document/WeChat Files/wxid_2gh9d5knc6th21/FileStorage/File/'
files = os.listdir(path)  # 列出当前文件夹的所有文件

# 循环遍历每个文件
for file in files:
    print(file)

    # 以扩展名为名称的子文件夹
    folder_name = path + file.split(".")[-1]
    print(folder_name)

    # 如果不存在该目录，先创建，再移动文件
    if not os.path.exists(folder_name):
        os.makedirs(folder_name)

        # 举例：这里的f为 1.png 等同于 ./1.png (因为是相对路径)
        shutil.move(file, folder_name)

    # 直接移动文件
    else:
        shutil.move(file, folder_name)