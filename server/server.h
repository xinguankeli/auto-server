#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "../info/host.h"
//p2p的服务端，只负责监听本地IPv6地址(::)和自定义端口
//这个类会被放到子线程中运行
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(quint16 port);
    ~Server();
private:
    //端口
    quint16 port;
    //QTCPServer
    QTcpServer *tcpServer;
    //本机信息
    host *local;
    //客户端和本地链接的所有socket
    QList<QTcpSocket*> tcpSocketList;
private slots:
    //创建新TCP链接槽函数
    void whenNewConnection();
    //客户端掉线处理
    void whenClientDisconnect();
    //客户端发来的数据处理
    void whenClientSendDataToMe();
};

#endif // SERVER_H
