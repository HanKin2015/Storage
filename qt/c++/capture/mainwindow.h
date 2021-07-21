#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QHBoxLayout>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QCamera *camera;
    QCameraViewfinder *cameravierfinder;
    QCameraImageCapture *cameraImageCapture;
    QLabel *displayLabel;
    QHBoxLayout *mainlayout;
    QList<QCameraInfo> cameraList;
    QComboBox *comboBox;
    void Init();
    void InitLayout();

private slots:
    void openBtnResponded();
    void closeBtnResponded();
    void captureBtnResponded();
    void saveBtnResponded();
    void exitBtnResponded();
    void cameraImageCaptured(int id, QImage image);
};
#endif // MAINWINDOW_H
