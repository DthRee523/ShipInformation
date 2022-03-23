#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    systemInit();
    initLoadingWindow();
    //测试代码
    connectSuccess();
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
    connect(ui->intoMainWindow_btn, &QPushButton::clicked, this, [=] {
        ui->stackedWidget->setCurrentIndex(1);//跳转主页面
    });
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

