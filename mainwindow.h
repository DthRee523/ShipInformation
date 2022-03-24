#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QString>
#include <QThread>

#include "tcpnetclient.h"

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

    void connectSuccess();

    void getNetData(BaseData data);

private:
    Ui::MainWindow *ui;

    TcpNetClient *tcp;

    double depth;//水深
    double headingAngle;//艏向角
    int compassDegrees;//指南针度数
};
#endif // MAINWINDOW_H
