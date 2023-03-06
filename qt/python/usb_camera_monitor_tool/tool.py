import os

count = 0
excludes = ''
with open('h.txt', 'r') as f:
    for line in f.readlines():
        count += 1
        if count < 3:
            continue
        line = line.strip()
        library_name = line.split(' ')[0]
        #print(library_name)
        if excludes == '':
            excludes = '\'{}\''.format(library_name)
        else:
            excludes = '{}, \'{}\''.format(excludes, library_name)
print(count)

with open('h_ret.txt', 'w') as f:
    f.write(excludes)