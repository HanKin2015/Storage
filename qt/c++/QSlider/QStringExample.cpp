#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QSlider>

void qStringPrepend()
{
    QString str = "World";

    // 在开头添加字符串
    str.prepend("Hello ");
    qDebug() << str;  // 输出："Hello World"

    // 在开头添加单个字符
    str.prepend('!');
    qDebug() << str;  // 输出："!Hello World"

    // 在开头添加 3 个 '-'
    str.prepend(QString('-').repeated(3));
    qDebug() << str;  // 输出："---!Hello World"
}

void qStringRemove()
{
    QString str = "Hello World! Hello Qt!";

    // 1. 删除指定位置和长度的字符：从索引 6 开始删除 5 个字符（即 "World"）
    str.remove(6, 5);
    qDebug() << str;  // 输出："Hello ! Hello Qt!"

    // 2. 删除所有匹配的字符串 "Hello "
    str.remove("Hello ");
    qDebug() << str;  // 输出："! Qt!"

    // 3. 删除所有感叹号（使用单个字符的字符串）
    str.remove("!");
    qDebug() << str;  // 输出：" Qt"
}

// 学习QString相关函数
void qStringExample()
{
    qStringPrepend();
    qStringRemove();

    QString str = "test";
    str.prepend("new_").remove(3, 2);  // 先添加前缀 "new_", 再删除索引3开始的2个字符
    qDebug() << str;  // 过程："test" → "new_test" → "newest"（删除索引3的 't' 和索引4的 '_'）
}

int main(int argc, char *argv[])
{
    qStringExample();

    QApplication a(argc, argv);
    QWidget *window = new QWidget;
    window->setWindowTitle("Enter your age");

    QSpinBox *spinBox = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);
    spinBox->setRange(0, 130);
    slider->setRange(0, 130);

    QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    spinBox->setValue(35);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    window->setLayout(layout);

    window->show();
    return a.exec();
}
