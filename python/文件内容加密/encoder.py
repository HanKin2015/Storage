# 忽然之间想到，我直接压缩加密不就行了？？？

content = ''
index = 0
with open('./notebook.json', encoding = 'utf-8') as fd:
    ch = fd.read(1)
    print(ch)
    content += ch
    
    index += 1
    #if index > 55:
    #    fd.close()

with open('./notebook.txt', 'w') as fd:
    fd.write(content)