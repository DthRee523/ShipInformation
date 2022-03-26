#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

class TimeThread : public QObject
{
    Q_OBJECT
public:
    explicit TimeThread(QObject *parent = nullptr);

    void timeWorking();

signals:
    void updateSignal();
};

#endif // TIMETHREAD_H
