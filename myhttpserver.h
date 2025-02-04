#ifndef MYHTTPSERVER_H
#define MYHTTPSERVER_H

#include <QObject>
#include <QThread>

class MyHttpServerWorker;

class MyHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyHttpServer(QObject *parent = nullptr);
    ~MyHttpServer();

    void start();       //开始线程
    void stop();        //结束线程

signals:
    void signalStart();
    void signalPlayIndex(int index, int times);
    //void showMsg(QString msg);

private:
    //QThread m_workerThread;
    MyHttpServerWorker *m_work = nullptr;
};

#endif // MYHTTPSERVER_H
