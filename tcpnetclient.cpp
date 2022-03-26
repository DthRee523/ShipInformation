#include "tcpnetclient.h"

TcpNetClient::TcpNetClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, [=](){
        BaseData baseData;
        QByteArray recvData = socket->readAll();
        qDebug() << "数据接收";
        QJsonDocument jsonData = QJsonDocument::fromJson(recvData);
        QJsonObject jsonObject;
        jsonObject = jsonData.object();
        baseData.COG = jsonObject.value("COG").toString().toStdString();
        baseData.SOG = jsonObject.value("SOG").toString().toStdString();
        baseData.HeadingAngle = jsonObject.value("HeadingAngle").toDouble();
        baseData.Latitude = jsonObject.value("Latitude").toString().toStdString();
        baseData.longitude = jsonObject.value("longitude").toString().toStdString();
        baseData.windData.CompassDegrees = jsonObject.value("CompassDegrees").toDouble();
        baseData.windData.Direction = jsonObject.value("Direction").toString().toStdString();
        baseData.windData.Speed = jsonObject.value("Speed").toDouble();
        baseData.waterDepth = jsonObject.value("waterDepth").toDouble();
        qDebug() << baseData.COG.c_str();
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
    if (socket->waitForConnected(10000))
    {
        emit connectStatus(true);
        return;
    }
    emit connectStatus(false);
}
