#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QHBoxLayout>
#include <QComboBox>
#include <QFile>
#include <QMessageBox>
#include <QCloseEvent>

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

    QCamera *camera;                        // 相机
    QCameraViewfinder *cameravierfinder;    // 取景器
    QCameraImageCapture *cameraImageCapture;// 图像捕获
    QLabel *displayLabel;
    QHBoxLayout *mainlayout;
    QList<QCameraInfo> cameraList;
    QComboBox *cameraNameCB;        // 摄像头名称下拉框
    QComboBox *cameraFormatCB;      // 摄像头格式下拉框
    QList<QVideoFrame::PixelFormat> pixelFormats;
    QComboBox *cameraResolutionCB;  // 摄像头分辨率下拉框
    QList<QSize> resolutions;
    QLabel *statusbarName;
    QLabel *statusbarFormat;
    QLabel *statusbarResolution;
    QLabel *statusbarBaiCheng;
    bool isExit;
    const QString APP_LOGO_FILE_PATH = ".\\image\\alienx64.png";
    const QString APP_LOG_FILE_PATH = ".\\capture.log";

    void Init();
    void InitLayout();

private slots:
    void openBtnResponded();
    void closeBtnResponded();
    void captureBtnResponded();
    void saveBtnResponded();
    bool sleep(unsigned int msec);
    bool deviceExist(const QCameraInfo &cameraInfo) const;
    void baichengBtnResponded();
    void cameraLog(QString msg);
    void exitBtnResponded();
    void cameraImageCaptured(int id, QImage image);

protected:
    void closeEvent(QCloseEvent* );
};
#endif // MAINWINDOW_H
