# 文件读取中常见的错误

## 1、使用 chardet 检测编码使用 errors 参数
```
import chardet

def detect_encoding(file_path):
    with open(file_path, 'rb') as f:
        result = chardet.detect(f.read())
    return result['encoding']

file_path = 'your_log_file.log'
encoding = detect_encoding(file_path)

with open(file_path, 'r', encoding=encoding) as f:
    for line in f:
        # 处理每一行
        print(line)
```

## 2、使用 errors 参数
```
file_path = 'your_log_file.log'

with open(file_path, 'r', encoding='utf-8', errors='ignore', errors='replace') as f:
    for line in f:
        # 处理每一行
        print(line)
```

## 3、windows不支持部分符号命名，但是Linux可以，如冒号（:）
```
import os
import zipfile

def sanitize_filename(filename):
    # 替换 Windows 不支持的字符
    return filename.replace(':', '_')

def unzip_file(zip_file_path, extract_path):
    with zipfile.ZipFile(zip_file_path, 'r') as zip_ref:
        for member in zip_ref.infolist():
            # 获取原始文件名
            original_filename = member.filename
            # 清理文件名
            sanitized_filename = sanitize_filename(original_filename)
            # 计算目标路径
            target_path = os.path.join(extract_path, sanitized_filename)

            # 如果是目录，确保目录存在
            if member.is_dir():
                os.makedirs(target_path, exist_ok=True)
            else:
                # 确保目标目录存在
                os.makedirs(os.path.dirname(target_path), exist_ok=True)
                # 解压文件
                with zip_ref.open(member) as source, open(target_path, 'wb') as target:
                    target.write(source.read())

            print(f"Extracted {original_filename} to {target_path}")

# 示例调用
zip_file_path = 'your_zip_file.zip'
extract_path = 'your_extract_path'
unzip_file(zip_file_path, extract_path)
```



