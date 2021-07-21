import itertools as its
import string
import time

# 1、string模块中的常量
numbers = string.digits                 # 包含0-9的字符串
letters = string.ascii_letters          # 包含a-z和A-Z的字符串
lower_letters = string.ascii_lowercase  # 包含a-z的字符串
print(numbers, letters, lower_letters)

"""
string.digits：数字0~9
string.ascii_letters：所有字母（大小写）
string.ascii_lowercase：所有小写字母
string.printable：可打印字符的字符串
string.punctuation：所有标点
string.ascii_uppercase：所有大写字母
"""

# 2、find函数
title = "Monty Python's Flying Circus"
print(title.find('Python')) # 索引从0开始(6)
print(title.find('python')) # 区分大小写(-1)
print(title.find('Python', 5))  # 5位置是空格(6)
print(title.find('Python', 6))  # 6位置是P(6)
print(title.find('Python', 7))  # 7位置是y(-1)
print(title.find('Python', 6, 11))  # 11位置是n(-1)
print(title.find('Python', 6, 12))  # 12位置是'(6)

# 3、join和split函数
seq = ['1', '2', '3', '4', '5']
sep = '+'
join_seq = sep.join(seq)
print(seq, join_seq)

split_seq = join_seq.split(sep)
print(join_seq, split_seq)

# 4、lower和upper函数
upper_letters = lower_letters.upper()
print(lower_letters, upper_letters)
upper_letters = upper_letters.lower()
print(lower_letters, upper_letters)

# 5、首字母大写之capwords和title函数
sentence = "that is ok, this's not ok."
print(sentence.title())
sentence_ = string.capwords(sentence)
print(sentence, sentence_)

# 6、replace和maketrans以及translate函数
table = sentence.replace('ok', 'good')
print(table, len(table))
table = str.maketrans('ab', 'xy')
print(table, len(table))
print(sentence.translate(table))    # 规则替换a变成x,b变成y

# 7、去除两侧空格的字符串strip函数
exam = "   ab cd efg   "
print(exam, exam.strip())       # 去除空格
print(exam, exam.strip(' g'))   # 去除空格和g



