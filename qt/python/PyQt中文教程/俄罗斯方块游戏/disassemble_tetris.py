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

class Tetris(QMainWindow):
    '''游戏主体类'''
    
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.tboard = Board(self)   # 创建了一个Board类的实例，并设置为应用的中心组件
        self.setCentralWidget(self.tboard)

        self.statusbar = self.statusBar()   # 创建一个statusbar来显示三种信息：消除的行数，游戏暂停状态或者游戏结束状态
        self.tboard.msg2Statusbar[str].connect(self.statusbar.showMessage)  # msg2Statusbar是一个自定义的信号，用在（和）Board类（交互）

        self.tboard.start()

        self.resize(200, 400)
        self.center()
        self.setWindowTitle('俄罗斯方块')
        self.setWindowIcon(QIcon('../icon/tencent.ico'))
        self.show()

    def center(self):
        '''居中显示'''
        
        screen = QDesktopWidget().screenGeometry()  # 显示屏的分辨率
        size = self.geometry()                      # 程序的大小
        print('screen resolution: {}x{}, application size: {}x{}'.format(screen.width(), screen.height(), size.width(), size.height()))
        self.move((screen.width()-size.width())/2, (screen.height()-size.height())/2)

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
        '''starts game'''
        print(len(self.board))
        if self.isPaused:
            return

        self.isStarted = True
        #self.isWaitingAfterLine = False
        self.numLinesRemoved = 0
        self.clearBoard()
        self.msg2Statusbar.emit(str(self.numLinesRemoved))

    def initBoard(self):     
        '''初始化画板'''

        #self.timer = QBasicTimer()
        #self.isWaitingAfterLine = False

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
        #self.clearBoard()
        
    def squareHeight(self):
        '''returns the height of one square'''

        return self.contentsRect().height() // Board.BoardHeight
    
    def clearBoard(self):
        '''清除画布上面所有方块，即重启游戏'''

        for i in range(Board.BoardHeight * Board.BoardWidth):
            self.board.append(Tetrominoe.NoShape)
            
    def shapeAt(self, x, y):
        '''determines shape at the board position'''

        return self.board[(y * Board.BoardWidth) + x]

    def squareWidth(self):
        '''returns the width of one square'''

        return self.contentsRect().width() // Board.BoardWidth

    def squareHeight(self):
        '''returns the height of one square'''

        return self.contentsRect().height() // Board.BoardHeight
        
    def drawSquare(self, painter, x, y, shape):
        '''draws a square of a shape'''        

        colorTable = [0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
                      0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00]
        color = QColor(colorTable[shape])   # 填充颜色
        painter.fillRect(x + 1, y + 1, self.squareWidth() - 2, 
            self.squareHeight() - 2, color)

        painter.setPen(color.lighter())
        painter.drawLine(x, y + self.squareHeight() - 1, x, y)
        painter.drawLine(x, y, x + self.squareWidth() - 1, y)
        painter.setPen(color.darker())
        painter.drawLine(x + 1, y + self.squareHeight() - 1,
            x + self.squareWidth() - 1, y + self.squareHeight() - 1)
        painter.drawLine(x + self.squareWidth() - 1, 
            y + self.squareHeight() - 1, x + self.squareWidth() - 1, y + 1)

    def paintEvent(self, event):
        '''画图'''

        painter = QPainter(self)
        rect = self.contentsRect()  # 还是不怎么理解
        print(rect)
        print('board size: {}x{}'.format(Board.BoardWidth, Board.BoardHeight))
        print(rect.bottom(), rect.top(), rect.left(), rect.right(), rect.height(), rect.width())
        
        boardTop = rect.bottom() - Board.BoardHeight * self.squareHeight()
        print('boardTop: {} {}'.format(boardTop, self.squareHeight()))
        
        print('piece count: {}'.format(len(self.board)))
        #print(help(self.drawSquare))
        for i in range(Board.BoardHeight):      # 画1x1的方块，即整个画布，先画横向，即一行一行的画
            for j in range(Board.BoardWidth):
                #print(j, Board.BoardHeight - i - 1)
                shape = self.shapeAt(j, Board.BoardHeight - i - 1)
                if shape != Tetrominoe.NoShape:
                    self.drawSquare(painter,
                        rect.left() + j * self.squareWidth(),
                        boardTop + i * self.squareHeight(), shape)
                #if i % 2 == 0:
                #    self.drawSquare(painter, rect.left()+j*self.squareWidth(), boardTop + i * self.squareHeight(), i%8)
                self.drawSquare(painter, rect.left()+j*self.squareWidth(), boardTop + i * self.squareHeight(), i%7+1)
        """
        if self.curPiece.shape() != Tetrominoe.NoShape:
            for i in range(4):
                x = self.curX + self.curPiece.x(i)
                y = self.curY - self.curPiece.y(i)
                self.drawSquare(painter, rect.left() + x * self.squareWidth(),
                    boardTop + (Board.BoardHeight - y - 1) * self.squareHeight(),
                    self.curPiece.shape())
        """

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
