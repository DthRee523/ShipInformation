#include "tcpnetclient.h"

TcpNetClient::TcpNetClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket;
    isConnected = false;
    connect(socket, &QTcpSocket::connected, this, [=](){
        emit connectStatus(true);
    });
    connect(socket, &QTcpSocket::readyRead, this, [=](){
        BaseData baseData;
        socket->read((char*)&baseData, sizeof (baseData));
        qDebug() << "数据接收";
        qDebug() << baseData.COG;
        emit sendData(baseData);
    });
    connect(socket, &QTcpSocket::disconnected, this, [=](){
        socket->deleteLater();
        emit connectStatus(false);
    });
}

void TcpNetClient::connectHost()
{
    socket->connectToHost(QHostAddress("127.0.0.1"), 8899);
    qDebug () << "客户端开始访问 子线程为：" << QThread::currentThreadId();
}