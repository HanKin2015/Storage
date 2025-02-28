#ifndef USBMANAGEMENT_H
#define USBMANAGEMENT_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QDesktopWidget>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QDebug>
#include <QScrollArea>
#include <QSize>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QButtonGroup>
#include <iostream>
#include <string>

class USBManagement : public QObject
{
    Q_OBJECT
public:
    USBManagement();
    ~USBManagement();

private:
    int SetupUI();

    //UI
    QWidget* mFullScreenMaskWidget;   //usb管理界面最底层覆盖全屏幕的透明窗口，
                                      //以实现全屏蒙版效果
    QWidget* mManagerWidget;
    QVBoxLayout* mManagerLayout;
    //ManagerTitleBar* mTitleBar;
    QLabel* mTipsLabel;
    QLabel* mPlaceHolder;
    //USBDevicePanel* mDevicePanel;
    //ManagerControlArea* mControlArea;

    //Data
    //QList<AppGroupData> mAppGroupsData;                 //程序组数据
    //QList<USBDeviceMappingData> mUsbDeviceMappingsData;     //usb设备信息及其映射关系
    /// 映射绑定功能相关
    //std::vector<UdevMappingBindTarget> mMappingBindTargets;   // 映射绑定的可选目标
    //std::map<std::string, UdevMappingBindTarget> mUdevBindingData;  // 记录device_id, bind target关系

public slots:
    void OkButtonClicked()
    {
        qDebug("OkButtonClicked");
    }
    void CancelButtonClicked()
    {
        qDebug("CancelButtonClicked");
    }
};

struct USBDeviceMappingData {
    std::string mUSBDeviceName;
    std::string mUSBDeviceVID;                  /// 十进制字符串存储
    std::string mUSBDevicePID;                  /// 十进制字符串存储
    std::string mUSBDeviceID;
    std::string mCurrentMappedSession;          /// 该设备当前映射的会话
    std::vector<std::string> mAllowedSession;   /// 该设备允许映射的会话
    std::string mBindTargetId;                  /// 该设备绑定到的目标的ID
                                                /// （绑定目标可以是独享桌面资源、远程应用资源）
};

struct AppData {
    std::string mAppName;       /// 程序名称
    std::string mAppIconFile;   /// 程序图标文件
};

struct AppGroupData {
    std::string mGroupName;         ///程序组（会话）名称
    std::string mGroupID;           ///程序组（会话）标识
    std::vector<AppData*> mApps;    ///程序组包含的程需
};

class AppGroup {
public:
    /**
     * @brief Construct a new AppGroup object
     *
     * @param manager 父usb设备管理器类
     * @param buttonGroup 所属按钮组
     * @param buttonID 按钮标识
     */
    AppGroup(USBManagement* manager, QButtonGroup* buttonGroup, int groupID)
    {
        mUsbDeviceManager = manager;
        mButtonGroup = buttonGroup;
        mButtonID = groupID;

        mGroupWidget = new QWidget();
        mGroupWidget->setObjectName("sessionAppGroupWidget");
        mGroupLayout = new QVBoxLayout();
        // 紧凑显示
        mGroupLayout->setSpacing(0);
        mGroupLayout->setMargin(0);
        mGroupHandler = new QRadioButton();
        mButtonGroup->addButton(mGroupHandler, mButtonID);

        mAppList = new QListWidget();
        mAppList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mAppList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // 以上图标下文字单行显示
        mAppList->setViewMode(QListView::IconMode);
        mAppList->setFlow(QListView::LeftToRight);
        mAppList->setMovement(QListView::Static);
        mAppList->setWrapping(false);
        // 限制icon图标大小，此处的值取自视觉稿
        mAppList->setIconSize(QSize(32, 32));

        mGroupLayout->addWidget(mGroupHandler);
        mGroupLayout->addWidget(mAppList);
        mGroupWidget->setLayout(mGroupLayout);
    }
    ~AppGroup();

public:
    /**
     * @brief 刷新程序列表
     *
     * @return int 0:成功，其他：失败
     */
    int ReFreshAppList();
    /**
     * @brief 获取主显示组件引用
     *
     * @return QWidget* 主显示组件引用
     */
    QWidget* GetMainWidget() { return mGroupWidget; }
    /**
     * @brief 获取radiobutton组件引用
     *
     * @return QWidget* radiobutton组件引用
     */
    QWidget* GetGroupHandler() {return mGroupHandler;}
    /**
     * @brief 获取按钮标识
     *
     * @return int 按钮标识
     */
    int GetButtonID() {return mButtonID;}
    /**
     * @brief 获取程序组标识
     *
     * @return QString 程序组ID
     */
    QString GetGroupID() {return QString::fromStdString(mAppGroupData->mGroupID);}
    /**
     * @brief 更新程序组数据
     *
     * @param groupData 用户组数据
     * @return int 0：成功，其他：失败
     */
    int UpdateGroupData(const AppGroupData* groupData);
    /**
     * @brief 清理程序组数据
     *
     * @return int 0：成功，其他：失败
     */
    int CleanGroupData();

public:
    //UI
    QWidget* mGroupWidget;          ///程序组主显示组件
    QVBoxLayout* mGroupLayout;      ///程序组显示组件布局
    QButtonGroup* mButtonGroup;     ///该程序组内的按钮组，同一个usb设备可映射的程序组属于同一个按钮组
    QRadioButton* mGroupHandler;    ///该程序组的选择器
    QListWidget* mAppList;          ///程序组的展示程序的列表组件

    QList<QListWidgetItem*> mAppListItems;  ///程序组内的程序列表组件
    USBManagement* mUsbDeviceManager;    ///USB设备管理器引用
    AppGroupData* mAppGroupData;            ///程序组数据
    int mButtonID;                          ///该程序组选择器的按钮标识
};

class USBDeviceItem : public QObject{
    Q_OBJECT
public:
    USBDeviceItem(USBManagement* manager, USBDeviceMappingData usbDeviceMappingData,
                           QObject* parent = 0)
    {
        Q_UNUSED(parent);
        mUSBDeviceManager = manager;
        mUSBDeviceMappingData = usbDeviceMappingData;
        mButtonGroup = new QButtonGroup();

        mDeviceItemWidget = new QWidget();
        mDeviceItemWidget->setObjectName("usbDeviceItemWidget");
        mDeviceItemLayout = new QVBoxLayout();

        // header
        mDeviceItemHeader = new QWidget();
        mDeviceItemHeader->setObjectName("usbDeviceItemHeader");
        mHeaderLayout = new QHBoxLayout();
        mHeaderText =  new QPushButton();
        mHeaderText->setObjectName("usbDeviceItemHeaderLeftNameButton");
        char buff[BUFSIZ];
        memset(buff, 0, sizeof(buff));
        qDebug("%s:%s", mUSBDeviceMappingData.mUSBDeviceVID.c_str(), mUSBDeviceMappingData.mUSBDevicePID.data());
        snprintf(buff, BUFSIZ-1, "%s(VID:PID %04X:%04X)", mUSBDeviceMappingData.mUSBDeviceName.c_str(),
                (uint16_t)std::stoul(mUSBDeviceMappingData.mUSBDeviceVID, NULL, 16),
               (uint16_t)std::stoul(mUSBDeviceMappingData.mUSBDevicePID, NULL, 16));
        mHeaderText->setText(QString(buff));

        mCheckBox = new QCheckBox(QObject::tr("Connect via default app:"));
        QString toolTipText;
        //在qt 4.8.7版本里，只能这么实现文本翻译替换
        //因为\n会导致翻译替换失败，只能单独为一个文本，不过效果没有变
        toolTipText.append(QObject::tr("1. If it is enabled, a USB device will be mapped to the server where the selected default app resides by default when it is connected for the first time."));
        toolTipText.append("\n");
        toolTipText.append(QObject::tr("2. This feature supports only servers with protocol V2.0."));
        mCheckBox->setToolTip(toolTipText);

        mEditBotton = new QPushButton(QObject::tr("Edit"));
        mEditBotton->setFixedSize(30, 20);
        // 设置编辑按钮的样式
        mEditBotton->setStyleSheet("QPushButton { background-color: transparent; color: blue; }");
        QObject::connect(mCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxStateChange(int)));
        QObject::connect(mEditBotton, SIGNAL(clicked()), this, SLOT(OpenButtonClicked()));
        //判断当前设备是否有绑定信息
        CheckDeviceBoundInfo();

        mHeaderArrow = new QPushButton();
        mHeaderArrow->setObjectName("usbDeviceItemHeaderRightActionButton");


        mHeaderLayout->setSpacing(0);
        mHeaderLayout->addWidget(mHeaderText);
        //这里添加一个text框
        mHeaderLayout->addStretch();
        mHeaderLayout->addWidget(mCheckBox);
        mHeaderLayout->addWidget(mEditBotton);
        mHeaderLayout->addWidget(mHeaderArrow);
        mDeviceItemHeader->setLayout(mHeaderLayout);

        // body
        mDeviceItemBody = new QWidget();
        mDeviceItemBody->setObjectName("usbDeviceItemBody");
        mDeviceItemBody->show();
        mBodyFolded = true;
        QObject::connect(mDeviceItemHeader,  SIGNAL(clicked()), this, SLOT(SwitchBodyFoldStatus()));
        QObject::connect(mHeaderText, SIGNAL(clicked()), this, SLOT(SwitchBodyFoldStatus()));
        QObject::connect(mHeaderArrow, SIGNAL(clicked()), this, SLOT(SwitchBodyFoldStatus()));
        mDeviceBodyLayout = new QGridLayout();
        mDeviceItemBody->setLayout(mDeviceBodyLayout);

        // main
        mDeviceItemLayout->addWidget(mDeviceItemHeader);
        mDeviceItemLayout->addWidget(mDeviceItemBody);
        mDeviceItemWidget->setLayout(mDeviceItemLayout);

        // 创建应用组框
        ReFreshDeviceMapping();
    }
    ~USBDeviceItem() {}

public:
    /**
     * @brief 刷新设备映射信息展示界面
     *
     * @return int
     */
    int ReFreshDeviceMapping();
    /**
     * @brief 获取主界面组件引用
     *
     * @return QWidget* 主界面组件引用
     */
    QWidget* GetMainWidget() {return mDeviceItemWidget; }
    QList<AppGroupData> GetAppGroupData() { return mAppGroupsData;}
    QCheckBox* GetCheckBox() {return mCheckBox;}
    QButtonGroup* GetButtonGroup() {return mAllAppButtonGroup;}
    void CheckDeviceBoundInfo() {}

private:
    //UI
    QWidget* mDeviceItemWidget;
    QVBoxLayout* mDeviceItemLayout;
    QWidget* mDeviceItemHeader;
    QPushButton* mHeaderText;
    QPushButton* mHeaderArrow;
    QHBoxLayout* mHeaderLayout;
    QWidget* mDeviceItemBody;
    QGridLayout* mDeviceBodyLayout;
    USBManagement* mUSBDeviceManager;
    QList<AppGroup*> mAppGroups;            // 该设备对应的可映射的会话
    QButtonGroup* mButtonGroup;

    QList<AppGroupData> mAppGroupsData;          // 程序组数据
    USBDeviceMappingData mUSBDeviceMappingData;  // 设备信息以及映射关系
    bool mBodyFolded;

    // @brief 映射绑定实现相关
    //BindTargetSelectPanel*  mAppData;
    bool mIgnoreBindCheckBoxEv;
    QCheckBox* mCheckBox;
    QPushButton* mEditBotton;
    QButtonGroup* mAllAppButtonGroup;
    /* 当前设备绑定的目标在MappingBindTargets中的位置下标 */
    int mBindTargetIndex;

public slots:
    void SwitchBodyFoldStatus() { qDebug("有鼠标点击折叠选项"); }
    void RadioButtonSlot() {}

    void OpenButtonClicked() {}
    void onCheckBoxStateChange(int state) { Q_UNUSED(state); }
};
#endif // USBMANAGEMENT_H
