#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

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
    void onNavItemClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    QListView *navListView;
    QStandardItemModel *navModel;

    // 用于创建各个页面的辅助函数
    QWidget* createBasicWidgetsPage();
    QWidget* createTextWidgetsPage();
    QWidget* createListWidgetsPage();
    QWidget* createSelectionWidgetsPage();
    QWidget* createContainerWidgetsPage();
};
#endif // MAINWINDOW_H
