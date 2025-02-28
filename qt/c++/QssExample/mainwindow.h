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
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomMenu : public QMenu
{
    Q_OBJECT

public:
    CustomMenu(const QString &title, QWidget *parent = nullptr)
        : QMenu(title, parent) {}
    virtual ~CustomMenu() {}

signals:
    void showEventSignal();

protected:
    bool event(QEvent *event) override {
        if (event->type() == QEvent::ToolTip) {
            QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
            QAction *action = actionAt(helpEvent->pos());
            if (action && !action->isEnabled()) {
                QToolTip::showText(helpEvent->globalPos(), action->toolTip(), this);
                return true; // 事件已处理
            } else {
                QToolTip::hideText();
            }
        }
        return QMenu::event(event); // 处理其他事件
    }

    void showEvent(QShowEvent *event) override {
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
    void RappSettings();	//虚拟应用设置

private:
    Ui::MainWindow *ui;
    QAction *mSbcAction;
};
#endif // MAINWINDOW_H
