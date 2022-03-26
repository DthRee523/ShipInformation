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
    x_index = 0;
    depth = 0;
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

    //设置两个角度旋钮
    ui->dial->setRange(0, 100);
    ui->dial_2->setRange(0, 360);
    ui->dial->setEnabled(false);
    ui->dial_2->setEnabled(false);

    //图表初始化
    chart = new QChart;
    ChartView = new QChartView(this);
    series = new QSplineSeries(chart);
    chart->addSeries(series);
    chart->setTitle("");

    axisX = new QValueAxis();
    axisY = new QValueAxis();

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);

    axisX->setTickCount(6);
    axisX->setRange(0, 10);
    axisY->setRange(0, 10);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    ChartView->setChart(chart);
    ui->verticalLayout->addWidget(ChartView);
    //添加时间线程
    QThread *timeSubThread = new QThread;
    TimeThread *timeThread = new TimeThread;
    connect(timeThread, &TimeThread::updateSignal, this, &MainWindow::updateChartView);
    connect(timeSubThread, &QThread::started, timeThread, &TimeThread::timeWorking);
    timeThread->moveToThread(timeSubThread);
    timeSubThread->start();
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
    //获取全部数据
    ui->COG_num_lab->setText(data.COG.c_str());
    ui->SOG_num_lab->setText(data.SOG.c_str());
    ui->latitude_str_lab->setText(data.Latitude.c_str());
    ui->longitude_str_lab->setText(data.longitude.c_str());
    ui->wind_direction_num_lab->setText(data.windData.Direction.c_str());
    ui->wind_speed_num_lab->setText(QString::number(data.windData.Speed));
    depth = data.waterDepth;
    ui->water_depth_num_lab->setText(QString::number(depth));
    headingAngle = data.HeadingAngle;
    compassDegrees = data.windData.CompassDegrees;
    //更新旋钮代替仪表盘
    ui->dial->setValue(this->headingAngle);
    ui->dial_2->setValue(this->compassDegrees);
}

/**
 * 更新图表
 * @brief MainWindow::updateChartView
 */
void MainWindow::updateChartView()
{
    qDebug() << "更新坐标系执行了" << x_index << "水深" << this->depth;
    series->append(x_index, depth / 10);
    double x = chart->plotArea().width() / 10;
    if(x_index > 10)
        chart->scroll(x,0);
    x_index ++;
}


