import pickle

data = '/home/jovyan/model/image_matrix_rfc.model'
file_path = './pickle.model'
with open(file_path, 'wb') as f:
    pickle.dump(data, f)

dic = {"k1":"v1", "k2":123}
s = pickle.dumps(dic)
print(s)

with open(file_path, 'rb') as f:
    data = pickle.load(f)
    
dic = {"k1":"v1", "k2":123}
s = pickle.dumps(dic)   # 序列化
dic2 = pickle.loads(s)  # 反序列化
print(dic2)

def check_charset(file_path):
    import chardet
    with open(file_path, "rb") as f:
        data = f.read(4)
        charset = chardet.detect(data)['encoding']
# 怀疑是不是数据量太大导致问题
big_file_path = './SangforLog2021-01-06_0.log'
#with open(big_file_path, 'r', encoding=check_charset(big_file_path)) as f:
with open(big_file_path, 'r', encoding='utf-16') as f:
    data = f.read()
# 存储为model格式
buffer = pickle.dumps(data)
with open(file_path, 'wb+') as f:
    f.write(buffer)
# 读取
with open(file_path, 'rb') as f:
    buffer = f.read()
model = pickle.loads(buffer)

