dict1 = {'a': 1, 'b': 2}
dict2 = {'b': 3, 'c': 4}
 
# 使用dict1的副本来避免修改原始字典
result = dict1.copy()
result.update(dict2)
 
print(result)  # 输出: {'a': 1, 'b': 3, 'c': 4}

dict1 = {'a': 1, 'b': 2}
dict2 = {'b': 3, 'c': 4}
 
# 直接合并两个字典
result = {**dict1, **dict2}
 
print(result)  # 输出: {'a': 1, 'b': 3, 'c': 4}