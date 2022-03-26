#include "timethread.h"

TimeThread::TimeThread(QObject *parent) : QObject(parent)
{

}

void TimeThread::timeWorking()
{
    qDebug() << "时间线程为" << QThread::currentThreadId();
    while(true)
    {
        emit updateSignal();
        QThread::sleep(1);//时间间隔一秒发送信号
    }
}
