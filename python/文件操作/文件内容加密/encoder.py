# 忽然之间想到，我直接压缩加密不就行了？？？

content = ''
index = 0
with open('./notebook.json', encoding = 'utf-8') as fd:
    ch = fd.read()  # 括号里可以指定读取的字符数量
    print(ch)
    fd.close()  # 不生效
    print('-' * 50)
    
    content += ch
    
    index += 1
    #if index > 55:
    #    fd.close()

with open('./notebook.txt', 'w') as fd:
    fd.write(content)
    
def test():
    with open('./notebook.json', encoding = 'utf-8') as fd:
        ch = fd.read()  # 括号里可以指定读取的字符数量
        print(ch)
        fd.close()  # 不生效
        print('-' * 50)
        return
        print('-' * 50)
test()