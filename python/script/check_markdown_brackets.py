# -*- coding: utf-8 -*-
"""
文 件 名: check_markdown_brackets.py
文件描述: 
作    者: HanKin
备    注: 
创建日期: 2025.09.18
修改日期：2025.09.18

Copyright (c) 2025 HanKin. All rights reserved.
"""
import re
import sys
import os

def check_markdown_brackets(file_path):
    """
    检查Markdown文件中是否包含大小写字母或连字符的未转义尖括号对
    
    参数:
        file_path: Markdown文件路径
    返回:
        错误列表，包含每个违规尖括号的位置和内容
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
    except FileNotFoundError:
        print(f"错误: 文件 '{file_path}' 不存在")
        return []
    except Exception as e:
        print(f"读取文件时出错: {str(e)}")
        return []

    errors = []
    line_num = 0
    in_code_block = False  # 标记是否在代码块内

    # 按行处理内容
    for line in content.splitlines():
        line_num += 1
        
        # 检查代码块标记，切换状态
        if '```' in line:
            in_code_block = not in_code_block
        
        # 如果在代码块内，跳过检查
        if in_code_block:
            continue
        
        # 正则表达式匹配：
        # - 未转义的<
        # - 中间包含至少一个字母(A-Za-z)或连字符(-)
        # - 未转义的>
        pattern = r'(?<!\\)<[A-Za-z-]+(?<!\\)>'
        # 考虑可能的转义反斜杠（偶数个反斜杠不算转义）
        # 更精确的模式，处理反斜杠转义情况
        pattern = r'(?<!\\)(?:\\\\)*<[A-Za-z-]+(?<!\\)(?:\\\\)*>'
        
        matches = re.finditer(pattern, line)
        for match in matches:
            position = match.start() + 1  # 列号(从1开始)
            matched_text = match.group()
            
            errors.append({
                'line': line_num,
                'position': position,
                'content': matched_text,
                'line_content': line
            })
    
    return errors

def main(file_path):
    errors = check_markdown_brackets(file_path)
    
    if errors:
        print(f"在文件 '{file_path}' 中发现 {len(errors)} 处未处理的尖括号:")
        for err in errors:
            print(f"行 {err['line']}, 列 {err['position']}: 发现未转义的 '{err['content']}'")
            #print(f"  内容: {err['line_content']}\n")
        #sys.exit(1)
    #else:
        #print(f"文件 '{file_path}' 中未发现不符合要求的尖括号")
        #sys.exit(0)

if __name__ == "__main__":
    file_dir = './'
    file_suffix = '.md'
    
    for root, dirs, files in os.walk(file_dir):
        for file in files:
            if os.path.splitext(file)[1] == file_suffix:
                main(os.path.join(root, file))
