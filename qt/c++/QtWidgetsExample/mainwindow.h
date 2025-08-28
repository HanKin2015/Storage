#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QListWidget>
#include <QMap>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNavItemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QListWidget *navList;          // 导航列表
    QStackedWidget *contentStack;  // 内容堆叠窗口
    QMap<QString, QList<QString>> navItems;  // 导航项数据
    QMap<QString, bool> expandStates;        // 保存展开状态
    QMap<QListWidgetItem*, QString> parentMap; // 子项到父项的映射

    void initUI();
    void initNavItems();
    void addNavGroup(const QString &groupName, const QStringList &items);
    void toggleGroup(const QString &groupName);
    QListWidgetItem* createGroupItem(const QString &text);
    QListWidgetItem* createSubItem(const QString &text, const QString &parent);
};
#endif // MAINWINDOW_H
