# -*- coding: utf-8 -*-
"""
Created on Mon Aug 24 13:12:09 2020

@author: Administrator
"""

import string

def love1():
    l = string.ascii_letters
    s = []
    s.append(l[34])
    s.append(l[11])
    s.append(l[14])
    s.append(l[21])
    s.append(l[4])
    s.append(l[24])
    s.append(l[14])
    s.append(l[20])
    s.insert(1, " ")
    s.insert(6, " ")
    ret = "".join(s)
    print(ret)  # I love you
    
    print(l)
    
def love2():
    print('\n'.join([''.join([('Love'[(x-y) % len('Love')] if ((x*0.05)**2+(y*0.1)**2-1)**3-(x*0.05)**2*(y*0.1)**3 <= 0 else ' ') for x in range(-30, 30)]) for y in range(30, -30, -1)]))

def love3():
    '''
    99669999996669999996699666699666999966699666699
    99699999999699999999699666699669966996699666699
    99669999999999999996699666699699666699699666699
    99666699999999999966666999966699666699699666699
    99666666999999996666666699666699666699699666699
    99666666669999666666666699666669966996699666699
    99666666666996666666666699666666999966669999996
    '''
    pass

from PIL import Image

def love4():
    mw = 100  # 照片宽度及高度
    ms = 30   # 每行最多放置照片数
    
    # 创建一张画布，关键是确定画布的大小
    toImage = Image.new('RGBA', (3000, 2000))
    
    for y in range(1, 21):  # 遍历行
        for x in range(1, 31):  # 遍历列
            try:
                # 选取照片，按照自己想要的样式，依次选取
                fromImage = Image.open(r"img/%s.jpg" % str(ms*(y-1)+x))
                # 调整照片大小
                fromImage = fromImage.resize((100, 100), Image.ANTIALIAS)
                # 粘贴照片，将照片粘贴到设计的位置上
                toImage.paste(fromImage, ((x-1)*mw, (y-1)*mw))
            except IOError:
                pass
    toImage.show()
    toImage.save('image.png')

if __name__ == "__main__":
    love1()
    print('----------------------')
    love2()
    print('----------------------')
    love4()
    
    
    
    
    
    
    
    
    
    
    
    
