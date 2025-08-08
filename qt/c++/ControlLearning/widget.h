#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

// 包含各种控件头文件
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QSlider>
#include <QScrollBar>
#include <QSpinBox>
#include <QDial>
#include <QProgressBar>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QToolButton>
#include <QToolBox>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QFrame>
#include <QScrollArea>
#include <QTabBar>
#include <QWhatsThis>
#include <QButtonGroup>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTabWidget *tabWidget;

    // 创建各个标签页的函数
    QWidget* createBasicControlsTab();
    QWidget* createTextControlsTab();
    QWidget* createListControlsTab();
    QWidget* createSelectionControlsTab();
    QWidget* createContainerControlsTab();
    QWidget* createOtherControlsTab();
    QWidget* createDialogsTab();

    // 辅助函数：创建带标题的分组框
    QGroupBox* createGroupBox(const QString& title);
};
#endif // WIDGET_H
