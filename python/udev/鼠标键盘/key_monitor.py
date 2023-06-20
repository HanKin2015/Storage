# -*- coding: utf-8 -*-ahello world
import sys, os
from pynput.keyboard import Controller, Key, Listener
from pynput import keyboard
import time

start=time.time()
end=time.time()
fun_start=0
time_interval=0
index=0
dict={'interval_times':0,'max_interval':0.,'interval_location':[]}
count=0
t_count = 0
ay_count = 0
sf_count = 0
count_dict={'first_time':0.,'first_p_to_second_r':0.}
keyBoard_dict={'Key.enter':'\n',
               'Key.space':' ',
               "Key.tab":'\t'}
#比较按键生成的两个txt文件，这里主要是为了实现当退格键按下后，
#对比退格前后文本的差异，这里可以自己延伸
def com_str(path, file1, file2):
    path1 = os.path.join(path, file1)
    path2 = os.path.join(path, file2)
    with open(path1, 'r', encoding='utf-8') as f:
        file1 = f.readlines()
    content1 = [str.strip().split() for str in file1]
    with open(path2, 'r', encoding='utf-8') as f:
        file2 = f.readlines()
    content2 = [str.strip().split() for str in file2]
    print("content1:", content1)
    print("content2:", content2)
    str1 = []
    str2 = []
    for sub_list in content1:
        str1.extend(sub_list)
    for sub_list in content2:
        str2.extend(sub_list)
    print("the str1:", str1, "the length:", len(str1))
    print("the str2:", str2, "the length:", len(str2))
    origanl_len = len(str1)
    print("extend", origanl_len)
    if len(str1) > len(str2):
        str2.extend([' '] * (len(str1) - len(str2)))
    elif len(str1) < len(str2):
        str1.extend([' '] * (len(str2) - len(str1)))
    index = 0
    indexs = []
    count = 0
    for i, j in zip(str1, str2):
        if i != j:
            indexs.append(index)
            count += 1
            if index < origanl_len - 1:
                print("the before...")
            else:
                print("the after...")
        index += 1
    if count == 1:
        print("single...")
    elif count>1:
        print("the sentence...")

#得到键入的值
def get_key_name(key):
    if isinstance(key, keyboard.KeyCode):
        with open(r'C:\Users\xhc010\Desktop\key_record.txt','a',encoding='utf-8') as f:
            f.write(key.char)
        with open(r'C:\Users\xhc010\Desktop\key_record1.txt','a',encoding='utf-8') as f:
            f.write(key.char)
        return key.char
    else:
        if str(key) in ['Key.enter','Key.space','Key.tab']:
            with open(r'C:\Users\xhc010\Desktop\key_record.txt', 'a',encoding='utf-8') as f:
                f.write(keyBoard_dict[str(key)])
            with open(r'C:\Users\xhc010\Desktopkey_record1.txt', 'a',encoding='utf-8') as f:
                f.write(keyBoard_dict[str(key)])
        if str(key) in ['Key.backspace']:
            com_str(r'C:\Users\xhc010\Desktop','key_record.txt','key_record1.txt')
        return str(key)

# 监听按压
def on_press(key):
    global fun_start,time_interval,index,dict,count,count_dict,ay_count
    fun_start = time.time()
    press_time = time.strftime('%Y-%m-%d %H:%M:%S')
    if count == 0:
        count_dict['first_time'] = fun_start
    if index == 0 or index == 1:
        time_interval = fun_start - start
        if index == 1 and time_interval > 2.:
            #停顿位置
            dict["interval_location"].append(key)
            #停顿次数
            dict['interval_times'] += 1
            #最长停顿
            dict['max_interval'] = time_interval if time_interval > dict['max_interval'] else dict['max_interval']
    index += 1

    ay_count += 1#监听的次数
    with open(r'C:\Users\xhc010\Desktop\key_record.txt', 'a',encoding='utf-8') as f:
        f.write("  %d-" % ay_count)
    with open(r'C:\Users\xhc010\Desktop\key_record1.txt', 'a',encoding='utf-8') as f:
        f.write("  %d-" % ay_count)

    get_key_name(key)
    #print("正在按压:", get_key_name(key))
    with open(r'C:\Users\xhc010\Desktop\key_record.txt', 'a',encoding='utf-8') as f:
        f.write("\n")
        f.write("press time is %s" % press_time)
        f.write("\n")


# 监听释放
def on_release(key):
    global start,fun_start, time_interval, index,count,count_dict, t_count, sf_count,ay_count
    count+=1
    if count==2:
        #第一个键按下到第二个键释放的时间
        count_dict['first_p_to_second_r']=time.time()-count_dict['first_time']
        count=0
    #按下一个键盘到释放的时间
    time_diff = time.time() - start-time_interval
    release_time = time.strftime('%Y-%m-%d %H:%M:%S')
    if time_diff >= 0.4:
        t_count += 1#粘连的次数
        print("键盘该按键粘连超过0.4s 第 %s 次 date is %s" % (t_count, release_time))
        with open(r'C:\Users\xhc010\Desktop\key_record.txt', 'a',encoding='utf-8') as f:
            f.write("\n")
            f.write("键盘该按键粘连超过0.4s 第 %s 次" % t_count)
            f.write("\n")
        with open(r'C:\Users\xhc010\Desktop\key_record1.txt', 'a',encoding='utf-8') as f:
            f.write("\n")
            f.write("键盘该按键粘连超过0.4s 第 %s 次" % t_count)
            f.write("\n")

    sf_count += 1#释放的次数
    with open(r'C:\Users\xhc010\Desktop\key_record.txt', 'a',encoding='utf-8') as f:
        f.write("  %d-" % sf_count)
    with open(r'C:\Users\xhc010\Desktop\key_record1.txt', 'a',encoding='utf-8') as f:
        f.write("  %d-" % sf_count)

    # print("the interval between first press and release: %.2fs , press_key is %s" % 
    #       (time_diff, get_key_name(key)))
    with open(r'C:\Users\xhc010\Desktop\key_record.txt', 'a',encoding='utf-8') as f:
        f.write("\n")
        f.write("the interval between first press and release: %.2fs , \
            press_key is %s " % (time_diff, get_key_name(key)))
        f.write("\n")
        f.write("release time is %s" % release_time)
        f.write("\n")
    start = time.time()
    index = 1
    
    if sf_count != ay_count:
        # release_time = time.strftime('%Y-%m-%d %H:%M:%S')
        with open(r'C:\Users\xhc010\Desktop\key_record.txt', 'a',encoding='utf-8') as f:
            f.write("******键盘按压和释放不同步******发生时间为 %s" % release_time)
        with open(r'C:\Users\xhc010\Desktop\key_record1.txt', 'a',encoding='utf-8') as f:
            f.write("******键盘按压和释放不同步******发生时间为 %s" % release_time)
        sf_count = ay_count
        print("******键盘按压和释放不同步******发生时间为 %s" % release_time)

    #print("已经释放:", get_key_name(key))
    if key == Key.esc:
        # 停止监听
        return False
    

# 开始监听
def start_listen():
    with Listener(on_press=on_press, on_release=on_release) as listener:
        listener.join()
    

if __name__ == '__main__':
    # 开始监听,按esc退出监听
    start_listen()
    print(dict)
    print("本次监听结束")
