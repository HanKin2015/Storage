#include "QtApplication1.h"

void QtApplication1::SetupUI()
{
    qDebug("%s", __FUNCTION__);

    mAppList = new QListWidget();
    mAppList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mAppList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mAppList->setViewMode(QListView::IconMode);
    mAppList->setFlow(QListView::LeftToRight);  // 以上图标下文字单行显示
    mAppList->setMovement(QListView::Static);

    QListWidgetItem *normalItem = new QListWidgetItem(QIcon(QString::fromStdString("://Resources/images/normal.png")),
        QString::fromStdString("normal"), mAppList);
    QListWidgetItem *abnormalItem = new QListWidgetItem(QPixmap::fromImage(QImage(QString::fromStdString("://Resources/images/abnormal.png"))),
        QString::fromStdString("abnormal"), mAppList);

    QIcon icon("://Resources/images/abnormal.png");     // 即使不为Null也显示失败了
    QImage image("://Resources/images/abnormal.png");
    QPixmap pixmap("://Resources/images/abnormal.png");
    if (icon.isNull()) {
        qDebug() << "Failed to load icon!";
    }
    if (image.isNull()) {
        qDebug() << "Failed to load image!";
    }
    if (pixmap.isNull()) {
        qDebug() << "Failed to load pixmap!";
    }
    else {
        qDebug() << "Pixmap loaded successfully!";
    }
    QByteArrayList formats = QImageReader::supportedImageFormats();
    qDebug() << "Supported image formats:" << formats;

    QImage image_;
    QImageReader reader("://Resources/images/abnormal.png");
    image_ = reader.read();
    if (image_.isNull()) {
        qDebug() << "Failed to load image!";
    }

    QFile file("://Resources/images/abnormal.png");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QImage img = QImage::fromData(data);
    if (img.isNull()) {
        qDebug() << "Failed to load image!";
    }

    QPixmap pix;
    if (file.open(QIODevice::ReadOnly)) {
        pix.loadFromData(file.readAll());
        qDebug() << "Pixmap loadFromData successfully!";
        file.close();
    }

    this->resize(800, 600);
    this->setObjectName(QString::fromUtf8("MainWindow"));
    this->setWindowTitle(QCoreApplication::translate("MainWindow", "QtExample", nullptr));
    //this->setWindowIcon(QPixmap::fromImage(img));
    this->setWindowIcon(pix);
    this->setCentralWidget(mAppList);
}

QtApplication1::QtApplication1(QWidget* parent)
    : QMainWindow(parent)
{
    SetupUI();
}

QtApplication1::~QtApplication1()
{
    delete mAppList;
}
