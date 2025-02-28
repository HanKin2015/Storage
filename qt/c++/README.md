# 项目说明

## 1、qt_example
qt示例，实现上面图标下面文字功能，文字添加工具提示框，图标涵盖png/gif/jpg/jpeg/ico格式。
注意：images文件夹需要放在build-qt_example-Desktop_Qt_5_14_2_MinGW_64_bit-Debug文件夹才能生效。

## 2、capture
实现摄像头打开功能。

## 3、StudyQml
学习Qml实现qt界面。




## 4、判断鼠标是否在组件上面
```
void checkMousePosition() {
    // 检查鼠标是否在悬浮框上
    QPoint pos = QCursor::pos();
    QRect widgetRect = QRect(mToolButton->mapToGlobal(mToolButton->rect().topLeft()), mToolButton->size());
    if (!underMouse() && !widgetRect.contains(pos)) {
        qDebug("hejian underMouse(): %d", underMouse());
        hideTooltip(); // 如果不在悬浮框上，隐藏悬浮框
    }
}
```

## 5、打印事件消息
```
bool event(QEvent *event) override
{
    // 获取当前时间
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // 获取事件类型
    int eventType = event->type();

    // 将事件类型转换为字符串
    QString eventTypeName = QEvent::staticMetaObject.enumerator(QEvent::staticMetaObject.indexOfEnumerator("Type")).valueToKey(eventType);

    // 输出当前时间和事件类型名称
    qDebug("%s: %s", currentTime.toStdString().c_str(), eventTypeName.toStdString().c_str());
    return QWidget::event(event);
}
```