from common import *

app = QApplication([])
tab_widget = QTabWidget()

# 创建第一个选项卡
tab1 = QWidget()
layout1 = QVBoxLayout()
layout1.addWidget(QLabel("这是第一个选项卡"))
tab1.setLayout(layout1)
tab_widget.addTab(tab1, "选项卡1")

# 创建第二个选项卡
tab2 = QWidget()
layout2 = QVBoxLayout()
layout2.addWidget(QLabel("这是第二个选项卡"))
tab2.setLayout(layout2)
tab_widget.addTab(tab2, "选项卡2")

tab_widget.show()
app.exec_()
