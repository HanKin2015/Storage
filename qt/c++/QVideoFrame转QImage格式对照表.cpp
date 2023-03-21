// Qt实现摄像头视频h264编码和拍照功能https://blog.csdn.net/qq853728579/article/details/126904620
#include <QApplication>
#include <QVideoFrame>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QList<QImage::Format> imageFormats = {
        QImage::Format_Invalid,
        QImage::Format_Mono,
        QImage::Format_MonoLSB,
        QImage::Format_Indexed8,
        QImage::Format_RGB32,
        QImage::Format_ARGB32,
        QImage::Format_ARGB32_Premultiplied,
        QImage::Format_RGB16,
        QImage::Format_ARGB8565_Premultiplied,
        QImage::Format_RGB666,
        QImage::Format_ARGB6666_Premultiplied,
        QImage::Format_RGB555,
        QImage::Format_ARGB8555_Premultiplied,
        QImage::Format_RGB888,
        QImage::Format_RGB444,
        QImage::Format_ARGB4444_Premultiplied,
        QImage::Format_RGBX8888,
        QImage::Format_RGBA8888,
        QImage::Format_RGBA8888_Premultiplied,
        QImage::Format_BGR30,
        QImage::Format_A2BGR30_Premultiplied,
        QImage::Format_RGB30,
        QImage::Format_A2RGB30_Premultiplied,
        QImage::Format_Alpha8,
        QImage::Format_Grayscale8,
        QImage::NImageFormats
    };

    QList<QVideoFrame::PixelFormat> pixelFormats = {
        QVideoFrame::Format_Invalid,
        QVideoFrame::Format_ARGB32,
        QVideoFrame::Format_ARGB32_Premultiplied,
        QVideoFrame::Format_RGB32,
        QVideoFrame::Format_RGB24,
        QVideoFrame::Format_RGB565,
        QVideoFrame::Format_RGB555,
        QVideoFrame::Format_ARGB8565_Premultiplied,
        QVideoFrame::Format_BGRA32,
        QVideoFrame::Format_BGRA32_Premultiplied,
        QVideoFrame::Format_BGR32,
        QVideoFrame::Format_BGR24,
        QVideoFrame::Format_BGR565,
        QVideoFrame::Format_BGR555,
        QVideoFrame::Format_BGRA5658_Premultiplied,

        QVideoFrame::Format_AYUV444,
        QVideoFrame::Format_AYUV444_Premultiplied,
        QVideoFrame::Format_YUV444,
        QVideoFrame::Format_YUV420P,
        QVideoFrame::Format_YV12,
        QVideoFrame::Format_UYVY,
        QVideoFrame::Format_YUYV,
        QVideoFrame::Format_NV12,
        QVideoFrame::Format_NV21,
        QVideoFrame::Format_IMC1,
        QVideoFrame::Format_IMC2,
        QVideoFrame::Format_IMC3,
        QVideoFrame::Format_IMC4,
        QVideoFrame::Format_Y8,
        QVideoFrame::Format_Y16,

        QVideoFrame::Format_Jpeg,

        QVideoFrame::Format_CameraRaw,
        QVideoFrame::Format_AdobeDng,

        QVideoFrame::NPixelFormats,
        QVideoFrame::Format_User
    };

    for (int i = 0 ; i < pixelFormats.count(); i++) {
        QImage::Format format = QVideoFrame::imageFormatFromPixelFormat(pixelFormats.at(i));
        qDebug()<<"|"<<pixelFormats.at(i)<<"|"<<(format ? "YES" : "NO")<<"|";
    }

    return app.exec();
}
