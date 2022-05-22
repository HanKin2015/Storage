# 导包
import configparser
config = configparser.ConfigParser() # 类实例化

# 定义文件路径
path = r'D:\Github\Storage\python\config\ini\conf.ini'

# 第一种读取ini文件方式,通过read方法
config.read(path)
value = config['select']['url']
print('第一种方法读取到的值：',value)

# 第二种读取ini文件方式，通过get方法
value = config.get('select','url')
print('第二种方法读取到的值：',value)

# 第三种读取ini文件方式，读取到一个section中的所有数据，返回一个列表
value = config.items('select')
print('第三种方法读取到的值：',value)

# 得到指定数据类型的数据
value = config.getint('connect_mysql','port')
print('这是第三种方法读取到的值：',value)
print('这是第三种方法读取到的值的数据类型：',type(value))

# 将数据写入到ini文件中(可能需要删除login块)
config.add_section('login') # 首先添加一个新的section
config.set('login','username','admin')  # 写入数据
config.set('login','password','123456') # 写入数据
config.write(open(path, 'w'))           # 保存数据

# 读取ini文件中所有的section
section = config.sections()
print(section)
