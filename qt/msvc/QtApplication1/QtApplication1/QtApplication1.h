#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QCoreApplication>
#include <QDebug>
#include <QImageReader>
#include <QFile>

class QtApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtApplication1(QWidget* parent = nullptr);
    void SetupUI();
    ~QtApplication1();

private:
    QListWidget* mAppList;

};
