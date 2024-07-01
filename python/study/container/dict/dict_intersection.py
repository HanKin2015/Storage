# 字典键的交集
dict1 = {'a': 1, 'b': 2, 'c': 3}
dict2 = {'b': 2, 'c': 3, 'd': 4}
key_intersection = dict1.keys() & dict2.keys()
 
# 字典值的交集
value_intersection = {v for k, v in dict1.items() if k in dict2}
 
print("键的交集:", key_intersection)
print("值的交集:", value_intersection)