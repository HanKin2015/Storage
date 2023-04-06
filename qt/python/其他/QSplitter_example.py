from PyQt5.QtWidgets import QApplication, QSplitter, QTextEdit

app = QApplication([])
splitter = QSplitter()

# 创建两个QTextEdit控件
text_edit1 = QTextEdit()
text_edit2 = QTextEdit()

# 将两个QTextEdit控件添加到QSplitter中
splitter.addWidget(text_edit1)
splitter.addWidget(text_edit2)

splitter.show()
app.exec_()
