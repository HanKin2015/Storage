#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QListWidget>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QSystemTrayIcon>
#include <QStatusBar>
#include <QToolButton>
#include <QToolTip>
#include <QHelpEvent>
#include <QMessageBox>
#include <QMenu>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomMenu : public QMenu
{
    Q_OBJECT

public:
    CustomMenu(QWidget *parent = nullptr) : QMenu(parent) {
        // 添加菜单项
        QAction *action1 = new QAction("Action 1", this);
        QAction *action2 = new QAction("Action 2", this);
        addAction(action1);
        addAction(action2);
    }

    CustomMenu(const QString &title, QWidget *parent = nullptr)
        : QMenu(title, parent) {
    }
    ~CustomMenu() {
    }


signals:
    void showEventSignal();

protected:
    bool event(QEvent *event) override {
        if (event->type() == QEvent::ToolTip) {
            QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
            QAction *action = actionAt(helpEvent->pos());
            if (action && !action->isEnabled()) {
            //if (action && action->objectName() == TOOLTIP_VISIBLE_ACTION) {
                qDebug("%s\n", action->text().toStdString().c_str());

                // 显示自定义工具提示
                QToolTip::showText(helpEvent->globalPos(), action->toolTip(), this);
                return true; // 事件已处理
            } else {
                // 如果鼠标不在该 action 上，隐藏工具提示
                QToolTip::hideText();
            }
        }
        //qDebug("%d\n", event->type());
        return QMenu::event(event); // 处理其他事件
    }
    void showEvent(QShowEvent *event) override {
        // 在菜单显示之前禁用 action1
        qDebug("showEvent the sub QMenu -> QAction!");
        emit showEventSignal();
        QMenu::showEvent(event); // 调用基类的 showEvent
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    int SetupUI();
    ~MainWindow();

private slots:
    void RappSettings();        // 应用设置
    void OpenUSBManagement();   // USB设备管理

private:
    Ui::MainWindow *ui;
    QAction *mSbcAction;
};
#endif // MAINWINDOW_H
