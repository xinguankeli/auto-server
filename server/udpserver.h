#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include "../info/host.h"
class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(quint16 port);
    ~UdpServer();
private:
    //端口
    quint16 port;
    //QUdpSocket
    QUdpSocket *udpSocket;
    //本机信息
    Host *local;
public:
    void listenning(int ipv);
private slots:
    //客户端发来的数据处理
    void whenClientSendDataTome();

public slots:
};

#endif // UDPSERVER_H
