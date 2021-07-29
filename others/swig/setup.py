#!/usr/bin/python
# -*- coding: UTF-8 -*-

# 利用python提供的自动化编译模块进行编译。编写一个编译文件setup.py
# 内容如下：(仅供参考,具体详细了解python自动化编译动态链接库文档)

from distutils.core import setup, Extension

# 生成一个扩展模块
test_swig_module = Extension('_test_swig',                  # 模块名称，必须要有下划线
                            sources=['test_swig_wrap.cxx',  # 封装后的接口cxx文件
                                    'test_swig.cpp'],
                            )

setup(name = 'test_swig',    # 打包后的名称
        version = '0.1',
        author = 'SWIG Docs',
        description = 'Simple swig pht from docs',
        ext_modules = [test_swig_module],   # 与上面的扩展模块名称一致
        py_modules = ['test_swig'],         # 需要打包的模块列表
    )
