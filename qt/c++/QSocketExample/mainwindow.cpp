#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TCP/UDP网络编程");
    resize(320, 100);

    QFormLayout *formLayout = new QFormLayout;

    QLineEdit *recvLineEdit = new QLineEdit;
    recvLineEdit->setReadOnly(true);
    recvLineEdit->setDisabled(true);
    formLayout->addRow(tr("&Recv:"), recvLineEdit);
    m_sendLineEdit = new QLineEdit;
    formLayout->addRow(tr("&Send:"), m_sendLineEdit);

    QPushButton *sendPushButton = new QPushButton;
    sendPushButton->setText("发送");
    connect(sendPushButton, &QPushButton::clicked, this, &MainWindow::sendPushButtonClicked);

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addLayout(formLayout);
    vBoxLayout->addWidget(sendPushButton);

    ui->centralwidget->setLayout(vBoxLayout);
}

void MainWindow::sendPushButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    qDebug() << QString("点击 {%1} 按钮了，发送内容为 {%2}").arg(btn->text()).arg(m_sendLineEdit->text());
}

MainWindow::~MainWindow()
{
    delete ui;
}
