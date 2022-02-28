#include "server.h"
#include <QDebug>
#include <QHostAddress>
Server::Server(quint16 port)
{
    this->port = port;
    local = new host();
    tcpServer = new QTcpServer();
    if(local->hasGlobalIPv6Address()){
        tcpServer->listen(QHostAddress::AnyIPv6, this->port);
        qDebug() << "[ipv6]";
    }else if(local->hasGlobalIPv4Address()){
        tcpServer->listen(QHostAddress::AnyIPv4, this->port);
        qDebug() << "[ipv4]";
    }else{
        qDebug() << "[Server start error]";
        return;
    }
    qDebug() << "[Server start listenning...]";
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
    qDebug() << "[client downline]";
    QTcpSocket *tcpSocket = static_cast<QTcpSocket *>(QObject::sender());
    tcpSocketList.removeOne(tcpSocket);
}

void Server::whenClientSendDataToMe()
{
    QTcpSocket *tcpSocket = static_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = tcpSocket->readAll();
    qDebug() << "[recv data from client]:" << data;
}
void Server::whenNewConnection()
{
    qDebug() << "[recv request from client]";
    //新的客户端发来请求
    QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
    //客户端的IP
    QHostAddress clientIPAddress = tcpSocket->peerAddress();
    //客户端的Port
    quint16 port = tcpSocket->peerPort();
    if(tcpSocketList.contains(tcpSocket)){
        qDebug() << "new client connection";
    }else{
        //记录客户端发来的请求
        tcpSocketList.append(tcpSocket);
        connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(whenClientDisconnect()));
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(whenClientSendDataToMe()));
    }
}


