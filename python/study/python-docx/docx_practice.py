# -*- coding: utf-8 -*-
"""
文 件 名: docx_practice.py
文件描述: 使用python-docx库实战，打开指定模板写排查报告
作    者: HanKin
创建日期: 2023.09.15
修改日期：2023.09.15
Copyright (c) 2023 HanKin. All rights reserved.
"""
import os
import time
from docx import Document       # 导入docx库
from docx.shared import Inches  # 导入英寸单位（可用于指定图片大小、表格宽高等）
from docx.enum.text import WD_PARAGRAPH_ALIGNMENT
from docx.enum.table import WD_CELL_VERTICAL_ALIGNMENT
from docx.oxml.ns import qn
from docx.shared import Pt

DOCX_FILE_PATH = '外设助手排查报告模板.docx'

def read_docx_table():
    """读取docx中所有表格内容，可以定位表格序号
    """

    document = Document(DOCX_FILE_PATH)

    # 读取表格内容
    for tb in document.tables:
        for i,row in enumerate(tb.rows):
            for j,cell in enumerate(row.cells):
                text = ''
                for p in cell.paragraphs:
                    text += p.text

                print(f'第{i}行，第{j}列的内容{text}')

def main():
    """主函数
    """
    
    #test()
    #table_style()
    #table_all_styles()
    #operate_old_docx()
    read_docx_table()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))