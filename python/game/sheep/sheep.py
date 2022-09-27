# 代码使用 pygame-zero 框架，看起来与一般代码稍有不同。可参考：https://pygame-zero.readthedocs.io/zh_CN/latest/

import pgzrun
import pygame
import random
import math
import os

# 定义游戏相关属性
TITLE = '白了个白' 
WIDTH = 600
HEIGHT = 720

# 自定义游戏常量
T_WIDTH = 60
T_HEIGHT = 66

# 下方牌堆的位置
DOCK = Rect((90, 564), (T_WIDTH*7, T_HEIGHT))

# 上方的所有牌
tiles = []
# 牌堆里的牌
docks = []

# 初始化牌组，12*12张牌随机打乱
ts = list(range(1, 13))*12
random.shuffle(ts)
n = 0
for k in range(7):    # 7层
    for i in range(7-k):    #每层减1行
        for j in range(7-k):
            t = ts[n]        #获取排种类
            n += 1
            tile = Actor(f'tile{t}')       #使用tileX图片创建Actor对象
            tile.pos = 120 + (k * 0.5 + j) * tile.width, 100 + (k * 0.5 + i) * tile.height * 0.9    #设定位置
            tile.tag = t            #记录种类
            tile.layer = k          #记录层级
            tile.status = 1 if k == 6 else 0        #除了最顶层，状态都设置为0（不可点）这里是个简化实现
            tiles.append(tile)
for i in range(4):        #剩余的4张牌放下面（为了凑整能通关）
    t = ts[n]
    n += 1
    tile = Actor(f'tile{t}')
    tile.pos = 210 + i * tile.width, 516
    tile.tag = t
    tile.layer = 0
    tile.status = 1
    tiles.append(tile)


# 游戏帧绘制函数
def draw():
    screen.clear()
    screen.blit('back', (0, 0))      #背景图
    for tile in tiles:
        #绘制上方牌组
        tile.draw()
        if tile.status == 0:
            screen.blit('mask', tile.topleft)     #不可点的添加遮罩
    for i, tile in enumerate(docks):
        #绘制排队，先调整一下位置（因为可能有牌被消掉）
        tile.left = (DOCK.x + i * T_WIDTH)
        tile.top = DOCK.y
        tile.draw()

    # 超过7张，失败
    if len(docks) >= 7:
        screen.blit('end', (0, 0))
    # 没有剩牌，胜利
    if len(tiles) == 0:
        screen.blit('win', (0, 0))


# 鼠标点击响应
def on_mouse_down(pos):
    global docks
    if len(docks) >= 7 or len(tiles) == 0:      #游戏结束不响应
        return
    for tile in reversed(tiles):    #逆序循环是为了先判断上方的牌，如果点击了就直接跳出，避免重复判定
        if tile.status == 1 and tile.collidepoint(pos):
            # 状态1可点，并且鼠标在范围内
            tile.status = 2
            tiles.remove(tile)
            diff = [t for t in docks if t.tag != tile.tag]    #获取牌堆内不相同的牌
            if len(docks) - len(diff) < 2:    #如果相同的牌数量<2，就加进牌堆
                docks.append(tile)
            else:             #否则用不相同的牌替换牌堆（即消除相同的牌）
                docks = diff
            for down in tiles:      #遍历所有的牌
                if down.layer == tile.layer - 1 and down.colliderect(tile):   #如果在此牌的下一层，并且有重叠
                    for up in tiles:      #那就再反过来判断这种被覆盖的牌，是否还有其他牌覆盖它
                        if up.layer == down.layer + 1 and up.colliderect(down):     #如果有就跳出
                            break
                    else:      #如果全都没有，说明它变成了可点状态
                        down.status = 1
            return

music.play('bgm')

pgzrun.go()