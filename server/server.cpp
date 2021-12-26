#include "server.h"
#include <QDebug>
#include <QHostAddress>
Server::Server(quint16 port)
{
    this->port = port;
    local = new host();
    tcpServer = new QTcpServer();
    tcpServer->listen(QHostAddress::AnyIPv6, this->port);
    qDebug() << "[Server开启监听]";
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(whenNewConnection()));
}

Server::~Server()
{
    tcpServer->close();
    delete tcpServer;
    delete local;
    deleteLater();
}
void Server::whenClientDisconnect()
{
    qDebug() << "[客户端掉线]";
    QTcpSocket *tcpSocket = static_cast<QTcpSocket *>(QObject::sender());
    tcpSocketList.removeOne(tcpSocket);
}

void Server::whenClientSendDataToMe()
{
    QTcpSocket *tcpSocket = static_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = tcpSocket->readAll();
    qDebug() << "[收到客户端的数据]:" << data;
}
void Server::whenNewConnection()
{
    qDebug() << "[有一个客户端发来请求]";
    //新的客户端发来请求
    QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
    //客户端的IP
    QHostAddress clientIPAddress = tcpSocket->peerAddress();
    //客户端的Port
    quint16 port = tcpSocket->peerPort();
    if(tcpSocketList.contains(tcpSocket)){
        qDebug() << "新客户端链接";
    }else{
        //记录客户端发来的请求
        tcpSocketList.append(tcpSocket);
        connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(whenClientDisconnect()));
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(whenClientSendDataToMe()));
    }
}


