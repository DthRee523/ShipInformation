#ifndef TCPNETCLIENT_H
#define TCPNETCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QtDebug>
#include <QThread>

#include "baseData.h"

class TcpNetClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpNetClient(QObject *parent = nullptr);

    void connectHost();

private:

    QTcpSocket *socket;

    bool isConnected;

signals:
    void connectStatus(bool status);
    void sendData(BaseData data);
};

#endif // TCPNETCLIENT_H
