# -*- coding: utf-8 -*-
"""
文 件 名: disassemble_tetris.py
文件描述: 俄罗斯方块游戏拆解学习
作    者: HanKin
创建日期: 2022.09.08
修改日期：2022.09.08

Copyright (c) 2022 HanKin. All rights reserved.
"""

from PyQt5.QtWidgets import QMainWindow, QFrame, QDesktopWidget, QApplication
from PyQt5.QtCore import Qt, QBasicTimer, pyqtSignal
from PyQt5.QtGui import QPainter, QColor, QIcon
import sys, random
from log import logger

class Tetris(QMainWindow):
    '''游戏主体类'''
    
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.tboard = Board(self)           # 创建了一个Board类的实例，并设置为应用的中心组件
        self.setCentralWidget(self.tboard)  # 这个引起了两次paintEvent事件

        self.statusbar = self.statusBar()   # 创建一个statusbar来显示三种信息：消除的行数，游戏暂停状态或者游戏结束状态
        self.tboard.msg2Statusbar[str].connect(self.statusbar.showMessage)  # msg2Statusbar是一个自定义的信号，用在（和）Board类（交互）
        logger.info(self.statusbar.contentsRect())
        logger.info('状态栏的大小: {}x{}'.format(self.statusbar.width(), self.statusbar.height()))
        logger.info(self.statusbar.size())
        self.statusbar.setStyleSheet('border-width: 0px;border-style: solid;border-color: rgb(255, 170, 0);background-color: rgb(200, 149, 237);')
        
        self.tboard.start()

        self.resize(200, 422)
        self.center()
        self.setWindowTitle('俄罗斯方块')
        self.setWindowIcon(QIcon('../icon/tencent.ico'))
        self.show()

    def center(self):
        '''居中显示'''
        
        screen = QDesktopWidget().screenGeometry()  # 显示屏的分辨率
        size = self.geometry()                      # 程序的大小
        logger.info('屏幕分辨率: {}x{}, 应用程序大小: {}x{}'.format(screen.width(), screen.height(), size.width(), size.height()))
        self.move((screen.width()-size.width())/2, (screen.height()-size.height())/2)

    #def paintEvent(self, event):
    #    print('here is statusbar real size:', self.statusbar.contentsRect())    # 默认大小为(100,30),第一次(200,18),第二次(200,22)

class Board(QFrame):
    '''画板类，即整个画布，整个方块填满的状态'''
    
    msg2Statusbar = pyqtSignal(str) # 创建了一个自定义信号msg2Statusbar，当我们想往statusbar里显示信息的时候，发出这个信号就行了
    BoardWidth = 10                 # 画板横向的方块个数，即方块大小为1x1
    BoardHeight = 20                # 画板纵向的方块个数，即方块大小为1x1
    Speed = 300                     # 每300ms出现一个新的方块

    def __init__(self, parent):
        super().__init__(parent)
        self.initBoard()

    def start(self):
        '''开始游戏'''

        if self.isPaused:
            logger.info('游戏已暂停')
            return
        self.isStarted = True
        self.isWaitingAfterLine = False
        self.numLinesRemoved = 0
        self.clearBoard()
        self.msg2Statusbar.emit(str(self.numLinesRemoved))
        
        self.newPiece()
        self.timer.start(Board.Speed, self)

    def initBoard(self):     
        '''初始化画板'''

        self.timer = QBasicTimer()
        self.isWaitingAfterLine = False # 定时器通过这个变量来判断是否需要

        self.curX = 0
        self.curY = 0
        self.numLinesRemoved = 0    # 分数，即消灭的行数
        self.board = []             # self.board定义了方块的形状和位置，取值范围是0-7
        
        self.setFocusPolicy(Qt.StrongFocus)
        
        self.setFrameShape(QFrame.Box)      # 给组件添加边框
        self.setFrameShadow(QFrame.Raised)
        self.setStyleSheet('border-width: 0px;border-style: solid;border-color: rgb(255, 170, 0);background-color: rgb(100, 149, 237);')
        #self.move(30, 30)

        self.isStarted = False
        self.isPaused = False
        self.clearBoard()

    def pause(self):
        '''暂停游戏'''

        if not self.isStarted:
            return

        self.isPaused = not self.isPaused

        if self.isPaused:
            self.timer.stop()
            self.msg2Statusbar.emit("游戏暂停")
        else:
            self.timer.start(Board.Speed, self)
            self.msg2Statusbar.emit(str(self.numLinesRemoved))
        self.update()

    def keyPressEvent(self, event):
        '''键盘按下事件'''

        if not self.isStarted or self.curPiece.shape() == Tetrominoe.NoShape:
            super(Board, self).keyPressEvent(event)
            return

        key = event.key()
        if key == Qt.Key_P:
            self.pause()
            return

        if self.isPaused:
            return
        elif key == Qt.Key_Left:
            self.tryMove(self.curPiece, self.curX - 1, self.curY)
        elif key == Qt.Key_Right:
            self.tryMove(self.curPiece, self.curX + 1, self.curY)
        elif key == Qt.Key_Down:
            self.tryMove(self.curPiece.rotateRight(), self.curX, self.curY)
        elif key == Qt.Key_Up:
            self.tryMove(self.curPiece.rotateLeft(), self.curX, self.curY)
        elif key == Qt.Key_Space:
            self.dropDown()
        elif key == Qt.Key_D:
            self.oneLineDown()  # D键是立即下降一行
        else:
            super(Board, self).keyPressEvent(event)

    def dropDown(self):
        '''空格键让方块快速下降到底部'''

        newY = self.curY
        while newY > 0:
            if not self.tryMove(self.curPiece, self.curX, newY - 1):
                break
            newY -= 1
        self.pieceDropped()

    def timerEvent(self, event):
        '''定时器事件'''

        if event.timerId() == self.timer.timerId():
            logger.debug('定时器id: {}'.format(event.timerId()))
            if self.isWaitingAfterLine: # 防止消除行的时候费时
                self.isWaitingAfterLine = False
                self.newPiece()
            else:
                self.oneLineDown()
        else:
            super(Board, self).timerEvent(event)

    def newPiece(self):
        '''创建一个方块'''

        self.curPiece = Shape()
        self.curPiece.setRandomShape()
        #self.curX = Board.BoardWidth // 2 + 1
        self.curX = Board.BoardWidth // 2 - 1
        self.curY = Board.BoardHeight - 1 + self.curPiece.minY()
        logger.info('随机方块第一次出现的位置: ({}, {})'.format(self.curX, self.curY))

        if not self.tryMove(self.curPiece, self.curX, self.curY):   # 超出了无法移动即游戏结束
            self.curPiece.setShape(Tetrominoe.NoShape)
            self.timer.stop()
            self.isStarted = False
            self.msg2Statusbar.emit("游戏结束")

    def tryMove(self, newPiece, newX, newY):
        '''判断以左上角坐标位置画方块是否超出画布背景'''

        for i in range(4):
            x = newX + newPiece.x(i)
            y = newY - newPiece.y(i)
            if x < 0 or x >= Board.BoardWidth or y < 0 or y >= Board.BoardHeight:
                return False
            if self.shapeAt(x, y) != Tetrominoe.NoShape:
                return False
        self.curPiece = newPiece
        self.curX = newX
        self.curY = newY
        self.update()
        return True

    def oneLineDown(self):
        '''方块下降一行'''

        if not self.tryMove(self.curPiece, self.curX, self.curY-1):   # 到达底部了
            self.pieceDropped()

    def pieceDropped(self):
        '''方块到达底部无法下降后，移除能消灭的所有行，然后再创建一个新的方块'''

        for i in range(4):
            x = self.curX + self.curPiece.x(i)
            y = self.curY - self.curPiece.y(i)
            logger.info('方块存储在数组中的位置: ({}, {}), {}'.format(x, y, (y*Board.BoardWidth)+x))
            self.setShapeAt(x, y, self.curPiece.shape())
        self.removeFullLines()

        if not self.isWaitingAfterLine: # 如果没有消除行的话创建新的方块
            self.newPiece()

    def removeFullLines(self):
        '''从board数组中判断能消灭的所有行并移除，并增加分数'''
        """
        如果方块碰到了底部，就调用removeFullLines()方法，找到所有能消除的行消除它们。
        消除的具体动作就是把符合条件的行消除掉之后，再把它上面的行下降一行。
        注意移除满行的动作是倒着来的，因为我们是按照重力来表现游戏的，如果不这样就有可能出现有些方块浮在空中的现象。
        """

        numFullLines = 0
        rowsToRemove = []
        for i in range(Board.BoardHeight):  # 每行进行判断是否有可消除的行，从下往上
            n = 0
            for j in range(Board.BoardWidth):
                if not self.shapeAt(j, i) == Tetrominoe.NoShape:
                    n = n + 1
            if n == Board.BoardWidth:   # 已修改，原程序不利于扩展，这句判断说明该行全是方块可消除
                rowsToRemove.append(i)

        rowsToRemove.reverse()  # 倒序处理，从上往下（不是很理解浮在空中的现象）

        for m in rowsToRemove:
            for k in range(m, Board.BoardHeight):   # 当前可消除的行往上
                for l in range(Board.BoardWidth):
                        self.setShapeAt(l, k, self.shapeAt(l, k+1)) # 当前行的形状变成上一行的形状，即颜色

        numFullLines = numFullLines + len(rowsToRemove)

        if numFullLines > 0:    # 有消除的话就需要增加分数
            self.numLinesRemoved = self.numLinesRemoved + numFullLines
            self.msg2Statusbar.emit(str(self.numLinesRemoved))

            self.isWaitingAfterLine = True
            self.curPiece.setShape(Tetrominoe.NoShape)
            self.update()

    def clearBoard(self):
        '''清除画布上面所有方块，即重启游戏'''

        for i in range(Board.BoardHeight * Board.BoardWidth):
            self.board.append(Tetrominoe.NoShape)
            
    def shapeAt(self, x, y):
        '''在board数组中该位置的形状，即方块颜色'''

        return self.board[(y*Board.BoardWidth)+x]

    def setShapeAt(self, x, y, shape):
        '''在board数组中添加新增的方块形状，即方块颜色'''

        self.board[(y*Board.BoardWidth)+x] = shape

    def squareWidth(self):
        '''计算方块的宽度'''

        return self.contentsRect().width() // Board.BoardWidth

    def squareHeight(self):
        '''计算方块的高度'''

        return self.contentsRect().height() // Board.BoardHeight
        
    def drawSquare(self, painter, x, y, shape):
        '''画方块'''        

        colorTable = [0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
                      0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00]
        color = QColor(colorTable[shape])                   # 填充颜色
        painter.fillRect(x+1, y+1, self.squareWidth()-2, self.squareHeight()-2, color)  # 填充中心方块
        #print(x+1, y+1, self.squareWidth()-2, self.squareHeight()-2)
        
        painter.setPen(color.lighter()) # 画左边和上边
        painter.drawLine(x, y, x, y+self.squareHeight()-1)  # 画竖线，减一是为了下面的有横线补充，参数为两个点的位置
        painter.drawLine(x, y, x+self.squareWidth()-1, y)   # 画横线，减一是为了右边的有横线补充，参数为两个点的位置
        
        painter.setPen(color.darker())  # 画下边和右边
        painter.drawLine(x+1, y+self.squareHeight()-1, x+self.squareWidth()-1, y+self.squareHeight()-1)
        painter.drawLine(x+self.squareWidth()-1, y+self.squareHeight()-1, x+self.squareWidth()-1, y+1)

    def paintEvent(self, event):
        '''画图'''

        logger.debug('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
        painter = QPainter(self)
        #print(help(painter.drawLine))
        rect = self.contentsRect()

        logger.debug(rect)
        logger.debug('画布背景的方块个数: {}x{}'.format(Board.BoardWidth, Board.BoardHeight))
        
        logger.debug('({}, {}, {}, {}), {}x{}'.format(rect.left(), rect.top(), rect.right(), rect.bottom(), rect.height(), rect.width()))
        #boardTop = rect.bottom() - Board.BoardHeight*self.squareHeight()
        #logger.debug('{}-{}*{}=boardTop: {}'.format(rect.bottom(), Board.BoardHeight, self.squareHeight(), boardTop))
        
        boardTop = rect.height() - Board.BoardHeight*self.squareHeight()    # 由于历史原因，不能使用bottom函数
        logger.debug('{}-{}*{}=boardTop: {}'.format(rect.height(), Board.BoardHeight, self.squareHeight(), boardTop))
        
        logger.debug('初始化后的方块总数: {}'.format(len(self.board)))
        logger.debug('方块的大小: {}x{}'.format(self.squareWidth(), self.squareHeight()))

        #print(help(self.drawSquare))
        for i in range(Board.BoardHeight):      # 画1x1的方块，即整个画布，先画横向，即一行一行的画
            for j in range(Board.BoardWidth):
                #print(j, Board.BoardHeight - i - 1)
                shape = self.shapeAt(j, Board.BoardHeight - i - 1)
                if shape != Tetrominoe.NoShape:
                    self.drawSquare(painter, rect.left()+j*self.squareWidth(), boardTop+i*self.squareHeight(), shape)
                #if i == 0:
                #    self.drawSquare(painter, rect.left()+j*self.squareWidth(), boardTop+i*self.squareHeight(), i%7+1)
                #self.drawSquare(painter, rect.left()+j*self.squareWidth(), boardTop + i * self.squareHeight(), i%7+1)

        if self.curPiece.shape() != Tetrominoe.NoShape:
            logger.debug('当前方块形状: {}'.format(self.curPiece.shape()))
            for i in range(4):
                x = self.curX + self.curPiece.x(i)
                y = self.curY - self.curPiece.y(i)
                logger.debug('形状坐标: ({}, {}), ({}, {}), ({}, {})'.format(x, y, self.curX , self.curY, self.curPiece.x(i), self.curPiece.y(i)))
                logger.debug('方块的左上角坐标位置: ({}, {})'.format(rect.left()+x*self.squareWidth(), boardTop+(Board.BoardHeight-y-1)*self.squareHeight()))
                self.drawSquare(painter, rect.left()+x*self.squareWidth(), boardTop+(Board.BoardHeight-y-1)*self.squareHeight(), self.curPiece.shape())

class Shape(object):
    """
    coordsTable元组保存了所有的方块形状的组成。是一个构成方块的坐标模版。
    游戏有7个基本形状：S、Z、T、L、反向L、直线、方块，每个形状都由4个方块组成
    数组将用来保存方块的坐标：y轴下边为正，x轴右边为正，以左上角为坐标原点
    每个点坐标代表的是每个方块的左上角位置坐标
    """
    
    # 空、Z、S、直线、T、方块、L、反向L
    coordsTable = (
        ((0, 0),     (0, 0),     (0, 0),     (0, 0)),
        ((0, -1),    (0, 0),     (-1, 0),    (-1, 1)),
        ((0, -1),    (0, 0),     (1, 0),     (1, 1)),
        ((0, -1),    (0, 0),     (0, 1),     (0, 2)),
        ((-1, 0),    (0, 0),     (1, 0),     (0, 1)),
        ((0, 0),     (1, 0),     (0, 1),     (1, 1)),
        ((-1, -1),   (0, -1),    (0, 0),     (0, 1)),
        ((1, -1),    (0, -1),    (0, 0),     (0, 1))
    )

    def __init__(self):
        self.coords = [[0,0] for i in range(4)] # 创建了一个新的空坐标数组，这个数组将用来保存方块的坐标
        self.pieceShape = Tetrominoe.NoShape
        self.setShape(Tetrominoe.NoShape)

    def shape(self):
        '''返回方块形状'''

        return self.pieceShape

    def setShape(self, shape):
        '''设置当前方块形状数据'''

        table = Shape.coordsTable[shape]
        for i in range(4):
            for j in range(2):
                self.coords[i][j] = table[i][j]
        self.pieceShape = shape

    def setRandomShape(self):
        '''选择一个随机形状的方块'''

        #randomNumber = random.randint(1, 7)
        randomNumber = 4
        logger.info('随机数为: {}'.format(randomNumber))
        self.setShape(randomNumber)

    def x(self, index):
        '''返回x轴坐标'''

        return self.coords[index][0]

    def y(self, index):
        '''返回y轴坐标'''

        return self.coords[index][1]

    def setX(self, index, x):
        '''设置x轴坐标'''

        self.coords[index][0] = x

    def setY(self, index, y):
        '''返回y轴坐标'''

        self.coords[index][1] = y

    def minX(self):
        '''返回x轴坐标最小值'''

        m = self.coords[0][0]
        for i in range(4):
            m = min(m, self.coords[i][0])
        return m

    def maxX(self):
        '''返回x轴坐标最大值'''

        m = self.coords[0][0]
        for i in range(4):
            m = max(m, self.coords[i][0])
        return m

    def minY(self):
        '''返回y轴坐标最小值'''

        m = self.coords[0][1]
        for i in range(4):
            m = min(m, self.coords[i][1])
        return m

    def maxY(self):
        '''返回y轴坐标最大值'''

        m = self.coords[0][1]
        for i in range(4):
            m = max(m, self.coords[i][1])
        return m

    def rotateLeft(self):
        '''向左翻转方块'''

        if self.pieceShape == Tetrominoe.SquareShape:
            return self

        result = Shape()
        result.pieceShape = self.pieceShape
        for i in range(4):
            result.setX(i, self.y(i))
            result.setY(i, -self.x(i))
        return result

    def rotateRight(self):
        '''向右翻转方块'''

        if self.pieceShape == Tetrominoe.SquareShape:
            return self

        result = Shape()
        result.pieceShape = self.pieceShape
        for i in range(4):
            result.setX(i, -self.y(i))
            result.setY(i, self.x(i))
        return result

class Tetrominoe(object):
    '''保存了所有方块的形状。我们还定义了一个NoShape的空形状'''
    
    NoShape = 0
    ZShape = 1
    SShape = 2
    LineShape = 3
    TShape = 4
    SquareShape = 5
    LShape = 6
    MirroredLShape = 7

if __name__ == '__main__':
    app = QApplication([])
    tetris = Tetris()
    sys.exit(app.exec_())
