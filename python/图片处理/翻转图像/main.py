'''
要翻转图像，我们需要使用 pygame.transform.flip(Surface, xbool, ybool) 方法，该方法被调用来根据我们的需要在垂直方向或水平方向翻转图像。

语法：
pygame.transform.flip(Surface, xbool, ybool)

缺少pygame库，需要安装：conda不行，pip install pygame即可

垂直翻转图像
我们在垂直方向上翻转图像。我们将使用 pygame.transform.flip() 来垂直显示图像。将 xbool 作为 True 和 ybool 作为 False 传递，这样图像就会垂直翻转。

水平方向翻转图像
我们在水平方向翻转图像。对于这个 xbool 作为 False 和 ybool 作为 True 传递，水平翻转它。
'''

# 导入 pygame 和 sys
import pygame
import sys
from pygame.locals import *

# 初始化pygame
# 导入模块
pygame.init()
pygame.display.set_caption('www.linuxmi.com')

# 图像大小将显示在屏幕上
screen = pygame.display.set_mode((1300, 600), 0, 32)

# pygame.image.load() 将返回
# 有图像的对象
img = pygame.image.load('linuxmi.com.png')

while True:

    # 背景颜色
    screen.fill((255, 255, 255))

    # 复制图像
    img_copy = img.copy()

    # pygame.transform.flip() 将翻转图像
    
    # 垂直翻转图像
    #img_with_flip = pygame.transform.flip(img_copy, False, True)
    
    # 水平翻转图像
    img_with_flip = pygame.transform.flip(img_copy, True, False)

    # surface.blit() 函数绘制一个源
    # 在这个表面上
    screen.blit(img_with_flip, (50 + 1 * 120, 100))

    # 退出屏幕的事件侦听器
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    # 每秒更新帧数
    pygame.display.update()