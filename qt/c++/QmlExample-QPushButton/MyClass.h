#ifndef MYCLASS_H
#define MYCLASS_H
#include <QDebug>
#include <QObject>

class MyClass : public QObject {
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void myFunction() {
        qDebug() << "Function called from QML!";
    }
};
#endif // MYCLASS_H
