import re

#第一步： grep -rn “_(.*)” ./ > new_temp
data = open("D:/Users/User/Desktop/res_1.txt", "r")
s = data.readlines()
data.close()

words_set = set()
for line in s:
    res = re.match('"[,"]', line)
    if res:
        words_set.add(res.group(1))
        print(res.group(1))
        #f.write(res.group(1))
        #f.write('\n')
    else:
        print('None')
with open("D:/Users/User/Desktop/words_json_res.txt", "w") as f:
    for word in words_set:
        print("word = %s" % word)
        f.write('"%s": "%s",\n' % (word, word))