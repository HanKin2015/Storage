#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel *label = new QLabel("<h2><font color='red'>Hello</font>, world!<h2>", this);
    label->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
