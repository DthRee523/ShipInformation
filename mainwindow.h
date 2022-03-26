#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QString>
#include <QThread>
#include <QChart>
#include <QChartView>
#include <QtCharts/QValueAxis>//用于显示坐标系
#include <QtCharts/QSplineSeries>
#include <QDateTime>

QT_CHARTS_USE_NAMESPACE

#include "tcpnetclient.h"
#include "timethread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initLoadingWindow();

    void systemInit();

public slots:
    //检测链接状态
    void connectSuccess();
    //获取网络数据
    void getNetData(BaseData data);
    //更新图表
    void updateChartView();

private:
    Ui::MainWindow *ui;

    TcpNetClient *tcp;//tcp连接

    double depth;//水深
    double headingAngle;//艏向角
    int compassDegrees;//指南针度数
    //图表基本信息
    QChart *chart;
    QChartView *ChartView;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QSplineSeries *series;
    int x_index;
};
#endif // MAINWINDOW_H
