# -*- coding: utf-8 -*-
"""
文 件 名: memory_leak.py
文件描述: 使用objgraph分析内存泄露
备    注: 
作    者: HanKin
创建日期: 2024.06.28
修改日期：2024.06.28

Copyright (c) 2024 HanKin. All rights reserved.
"""

def memory_usage_psutil():
    # return the memory usage in MB
    import psutil,os
    process = psutil.Process(os.getpid())
    mem = process.memory_info()[0] / float(2 ** 20)
    return mem

def get_current_obj(a=[]):
    a.append([0]*1000)
    return a

#@profile
def main():
    obj = []
    for i in range(10000):
        obj = get_current_obj(obj)
        #import gc
        #gc.collect()
        if(i%100==0):
            print(memory_usage_psutil())
    
    import objgraph
    print('-'*100)
    
    # 全局类型数量
    objgraph.show_most_common_types(limit=50)
    
    print('-'*100)
    
    # 增量变化
    objgraph.show_growth(limit=30)
    
    print('-'*100)
    
    # 在需要分析时，调用objgraph的函数
    # 查看对象图中对象的数量
    objgraph.show_growth()
    
    print('*' * 100)
    # Counting the number of obj objects in the GC.
    print(objgraph.count(obj))
    print('*' * 100)
    # Returning a list of obj objects in the GC.
    print(objgraph.by_type(obj))
    print('*' * 100)
    # Showing the back references of the obj object.
    #print.show_backrefs(obj)
    
    # 查看对象图中最常见的类型和数量
    objgraph.show_most_common_types()
     
    # 查看对象图中引用次数最多的对象
    #objgraph.show_most_common_nodes()
     
    # 查看对象图中对象的存储情况
    #objgraph.show_refs()
     
    # 查看对象图中对象的存储情况，并进行排序
    #objgraph.show_largest_by_attr('size')
     
    # 查看对象图中对象的存储情况，并进行排序
    #objgraph.show_backrefs(some_object)

if __name__=='__main__':
    main()