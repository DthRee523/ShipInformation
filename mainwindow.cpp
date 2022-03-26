#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcp = new TcpNetClient;
    initLoadingWindow();
    systemInit();
    //测试代码
    //connectSuccess();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * 初始化加载界面
 * @brief MainWindow::initLoadingWindow
 */
void MainWindow::initLoadingWindow()
{
    ui->connectTip_label->setText("正在连接服务器");
    //设置进入系统按钮不可见
    ui->intoMainWindow_btn->hide();
    //显示动图
    QMovie *loadingGif = new QMovie("../ShipInformation/src/loading.gif");
    loadingGif->start();
    ui->loadingImage_lab->setMovie(loadingGif);
    ui->loadingImage_lab->setScaledContents(true);
}

/**
 * 系统初始化
 * @brief MainWindow::systemInit
 */
void MainWindow::systemInit()
{
    QThread *subThread = new QThread;
    connect(ui->intoMainWindow_btn, &QPushButton::clicked, this, [=] {
        ui->stackedWidget->setCurrentIndex(1);//跳转主页面
    });
    connect(tcp, &TcpNetClient::connectStatus, this, [=](bool status){
        if (status)
        {
            connectSuccess();
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(0);
            ui->connectTip_label->setText("服务器断开链接！");
            ui->intoMainWindow_btn->setEnabled(false);
        }
    });
    qRegisterMetaType<BaseData>("BaseData");
    connect(tcp, &TcpNetClient::sendData, this, &MainWindow::getNetData);
    connect(subThread, &QThread::started, tcp, &TcpNetClient::connectHost);
    tcp->moveToThread(subThread);
    qDebug() << "当前线程为：" << QThread::currentThreadId();
    subThread->start();
}

/**
 * 连接成功函数
 * @brief MainWindow::connectSuccess
 */
void MainWindow::connectSuccess()
{
    ui->connectTip_label->setText("连接成功！");
    ui->loadingImage_lab->hide();
    ui->intoMainWindow_btn->show();
}

/**
 * 更新数据
 * @brief MainWindow::getNetData
 * @param data
 */
void MainWindow::getNetData(BaseData data)
{
    ui->COG_num_lab->setText(data.COG.c_str());
    ui->SOG_num_lab->setText(data.SOG.c_str());
    ui->latitude_str_lab->setText(data.Latitude.c_str());
    ui->longitude_str_lab->setText(data.longitude.c_str());
    ui->wind_direction_num_lab->setText(data.windData.Direction.c_str());
    ui->wind_speed_num_lab->setText(QString::number(data.windData.Speed));
    depth = data.waterDepth;
    ui->water_depth_num_lab->setText(QString::number(depth));
    headingAngle = data.HeadingAngle;
    compassDegrees = data.HeadingAngle;
}

