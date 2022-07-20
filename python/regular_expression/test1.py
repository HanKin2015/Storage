import re

#第一步： 在D:/Users/sangfor/Desktop/code/hermes/hermes下执行命令 grep -rn “_(.*)” ./ > new_temp
data = open("D:/Users/User/Desktop/new_temp.txt", "r", encoding="utf8")
s = data.readlines()
data.close()

words_set = set()
for line in s:
    #line = line.strip('\n')
    #print(line)
    res = re.match('._(u(.))+_.*', line)
    if res:
        words_set.add(res.group(1))
        print(res.group(1))
        #f.write(res.group(1))
        #f.write('\n')
with open("D:/Users/User/Desktop/res_1.txt", "w") as f:
    for word in words_set:
        print("word = %s" % word)
        res = re.match('(.*[,"])', word)
        if res:
            print("-res = %s" % res.group(1))
            f.write(res.group(1))
        else:
            print("res = %s" % word)
            f.write(word)
            f.write('\n')