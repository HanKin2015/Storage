import numpy as np

if __name__ == '__main__':
    dict = {'name':'hejian', 'sex':'man'}
    print(dict)
    print(type(dict))
    dict.get('age','22')
    print(type(dict.get('phone')))
    print(dict)
    # print(dict['age'])
    print(dict.get('face','handsome'))
    print(dict)
    print(dict.get('name'))
    print(dict['name'])
    print(dict.get('age'))
    # print(dict['age'])    #这条语句会报错
    print(dict.get('ds'))   #不存在的键不会报错，返回None（默认值）

    dict.get('name', 'huang')  # 并不会改变值
    print(dict)