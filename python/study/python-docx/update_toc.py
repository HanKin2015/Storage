# -*- coding: utf-8 -*-
"""
文 件 名: update_toc.py
文件描述: 目前的 python-docx 库不支持直接更新 Word 文档中的目录
作    者: HanKin
创建日期: 2023.09.18
修改日期：2023.09.18
Copyright (c) 2023 HanKin. All rights reserved.
"""

from docx import Document
from docx.oxml.ns import qn

# 打开一个 Word 文档
document = Document('update_toc.docx')

# 获取命名空间
nsmap = {
    'w': qn('http://schemas.openxmlformats.org/wordprocessingml/2006/main'),
    'w14': qn('http://schemas.microsoft.com/office/word/2010/wordml'),
    'w15': qn('http://schemas.microsoft.com/office/word/2012/wordml'),
    'w16se': qn('http://schemas.microsoft.com/office/word/2015/wordml/symex'),
    'wpg': qn('http://schemas.microsoft.com/office/word/2010/wordprocessingGroup'),
    'wp': qn('http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing'),
    'wpi': qn('http://schemas.microsoft.com/office/word/2010/wordprocessingInk'),
    'wne': qn('http://schemas.microsoft.com/office/word/2006/wordml'),
    'wps': qn('http://schemas.microsoft.com/office/word/2010/wordprocessingShape'),
}

# 查找目录元素
toc = document.element.xpath('//w:sdt[w:sdtPr/w:tag[@w:val="Table of Contents"]]', namespaces=nsmap)[0]

# 更新目录
toc_element = toc.getparent()
toc_element.remove(toc)
new_toc = OxmlElement('w:sdt')
new_tocPr = OxmlElement('w:sdtPr')
new_tocPr.append(OxmlElement('w:docPartObj'))
new_tocPr.append(OxmlElement('w:sdtEndPr'))
new_toc.append(new_tocPr)
new_toc.append(OxmlElement('w:sdtContent'))
toc_element.append(new_toc)

# 保存文档
document.save('update_toc_done.docx')

