import QtQuick 2.4
import QtQuick.Window 2.2
import QtMultimedia 5.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Window {
    visible: true
    width:  Qt.platform.os === "android"? Screen.width: 640
    height:  Qt.platform.os === "android"? Screen.height: 480
    color:"black";
    property var cameras: QtMultimedia.availableCameras
    property int currentCamera: 0

    FlatButton {
       id:qiehuan
       anchors.right: parent.right;
       anchors.rightMargin: 2;
       anchors.top: parent.top;
       iconSource: "res/11.png";
       width:Qt.platform.os === "android"? Screen.width/8:70;
       height: Qt.platform.os === "android"? Screen.width/8:70;
       iconHeight: Qt.platform.os === "android"? Screen.width/10:84;
       iconWidth: Qt.platform.os === "android"? Screen.width/10:84;
          visible: true;
         z:1
          onClicked: {
             currentCamera++
              if (currentCamera >= cameras.length)
                 currentCamera = 0
              camera.deviceId = cameras[currentCamera].deviceId
         }
      }
 Camera{
     id:camera;
     captureMode: Camera.CaptureStillImage;//捕获静态图像
     focus{
         focusMode:Camera.FocusAuto;//自动变焦
         focusPointMode: Camera.FocusPointCenter;//中心焦点
     }
     imageProcessing{
         whiteBalanceMode:CameraImageProcessing.WhiteBalanceAuto;//白平衡自动
     }
     flash.mode:Camera.FlashAuto;//闪光灯自动
     imageCapture{
         resolution: Qt.size(1280,960);
         onImageCaptured: {
            camera.stop();
             photoPreview.visible=true;
             actionBar.visible=false;
             viewfinder.visible=false;
             photoPreview.source=preview;
                  qiehuan.visible=false;
         }
         onImageSaved: {
             console.log(path);
         }
         }
         onLockStatusChanged:{
             switch(lockStatus)
             {
             case Camera.Locked:
                 imageCapture.captureToLocation("camera.jpg");
                 unlock();
                 break;
             case Camera.Searching:
                 console.log("searching");
                 break;
             case Camera.unlocked:
                 console.log("unlocked");
                 break;
             }
         }
 }
 VideoOutput{
     id:viewfinder;
     source: camera;
     focus:visible;
     anchors.fill:parent;
     autoOrientation: true;
}
Image{
    id:photoPreview;
    anchors.fill:parent;
    visible: false;
    fillMode: Image.PreserveAspectFit;
    FlatButton{
        iconSource: "res/ic_launcher_camera.png";
        width: Qt.platform.os === "android"? Screen.width/8: 76  ;
        height:  Qt.platform.os === "android"? Screen.width/8: 76  ;
        iconHeight: Qt.platform.os === "android"? Screen.width/10:84;
        iconWidth: Qt.platform.os === "android"? Screen.width/10:84;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.margins: 4;
        onClicked: {
            camera.start();
            actionBar.visible=true;
            viewfinder.visible=true;
            photoPreview.visible=false;
            qiehuan.visible=true;
        }
    }
}
Image
{
    id:actionBar;
    source:"res/control_bar.png";
    width:Qt.platform.os === "android"? Screen.width: 640;
        height:Qt.platform.os === "android"? Screen.height/10: 80;
    anchors.bottom: parent.bottom;
    anchors.bottomMargin: 8;
    anchors.horizontalCenter: parent.horizontalCenter;
    visible: true;
    z:1;
    FlatButton{
        id:shutter;
        anchors.centerIn: parent;
        iconSource: "res/ic_cam_shutter.png";
        width:Qt.platform.os === "android"? Screen.width/7:88;
        height: Qt.platform.os === "android"? Screen.width/7:88;
        iconHeight: Qt.platform.os === "android"? Screen.width/10:84;
        iconWidth: Qt.platform.os === "android"? Screen.width/10:84;
        onClicked: {
            camera.searchAndLock();//计算并锁定图像，触发锁定信号
        }
    }
    FlatButton{
        id:zoomout;
        anchors.verticalCenter: shutter.verticalCenter;
        anchors.right: shutter.left;
        anchors.rightMargin: 4;
        width:Qt.platform.os === "android"? Screen.width/7:70;
        height: Qt.platform.os === "android"? Screen.width/7:70;
        iconHeight: Qt.platform.os === "android"? Screen.width/10:84;
        iconWidth: Qt.platform.os === "android"? Screen.width/10:84;
        text:"缩小";
        font.pointSize: 12;
        iconSource: "res/ic_zoom_out.png";
        onClicked: {
            if(camera.digitalZoom>1)
                camera.digitalZoom=-0.5;
        }
    }
FlatButton{
    id:zoomin;
    anchors.verticalCenter: shutter.verticalCenter;
    anchors.right: zoomout.left;
    anchors.rightMargin: 4;
    width:Qt.platform.os === "android"? Screen.width/7:70;
    height: Qt.platform.os === "android"? Screen.width/7:70;
    iconHeight: Qt.platform.os === "android"? Screen.width/10:84;
    iconWidth: Qt.platform.os === "android"? Screen.width/10:84;
    text:"放大";
    font.pointSize: 12;
    iconSource: "res/ic_zoom_in.png";
    onClicked: {
    if(camera.digitalZoom<camera.maximumDigitalZoom)
    camera.digitalZoom+=0.5;
    }
}
FlatButton{
    id:currentFlath;
    anchors.verticalCenter: shutter.verticalCenter;
    anchors.left: shutter.right;
    anchors.leftMargin: 4;
    width:Qt.platform.os === "android"? Screen.width/7:70;
    height: Qt.platform.os === "android"? Screen.width/7:70;
    iconHeight: Qt.platform.os === "android"? Screen.width/10:84;
    iconWidth: Qt.platform.os === "android"? Screen.width/10:84;
    font.pointSize: 12;
    property var   moderIcon:["res/ic_menu_stat_flash_auto.png","res/ic_menu_stat_flash.png","res/ic_menu_stat_flash_off.png"]
    property var  moderDesc:["自动","打开","关闭"]
    property var flashMode: [
        Camera.FlashAuto, Camera.FlashOn, Camera.FlashOff
    ]
    property int mode: 0;
    text: moderDesc[mode];
    iconSource: moderIcon[mode];
    onClicked: {
        mode = (mode + 1)%3;
        camera.flash.mode = flashMode[mode];
    }
    }
FlatButton{
    id:currentScense;
    anchors.verticalCenter: shutter.verticalCenter;
    anchors.left: currentFlath.right;
    anchors.leftMargin: 4;
    width:Qt.platform.os === "android"? Screen.width/7:70;
    height: Qt.platform.os === "android"? Screen.width/7:70;
    iconHeight: Qt.platform.os === "android"? Screen.width/10:84;
    iconWidth: Qt.platform.os === "android"? Screen.width/10:84;
    font.pointSize: 12;
    property var  modeIcon: ["res/ic_menu_stat_auto.png","res/ic_menu_stat_portrait.png","res/ic_menu_stat_landscape.png","res/ic_menu_stat_night.png","res/ic_menu_stat_action.png"]
    property var modeDesc:["自动","人物","风景","夜间","运动"]
    property var exposureMode:[Camera.ExposureAuto,Camera.ExposurePortrait,Camera.ExposureBeach,Camera.ExposureNight,Camera.ExposureSports]
    property int  mode:0;
    text:modeDesc[mode];
    iconSource: modeIcon[mode];
    onClicked: {
        mode=(mode+1)%5;
        camera.exposure.exposureMode=exposureMode[mode];
    }
 }
  }
}
