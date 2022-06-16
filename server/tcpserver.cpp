#include "tcpserver.h"
#include <QDebug>
TcpServer::TcpServer(quint16 port)
{
    this->port = port;
    local = new Host();
    tcpServer = new QTcpServer();
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(whenNewConnection()));
}

TcpServer::~TcpServer()
{
    tcpServer->close();
    delete tcpServer;
    delete local;
    deleteLater();
}

void TcpServer::listenning(int ipv)
{
    if(ipv != 4 && ipv != 6){
        qDebug() << "[ip version error]";
        return;
    }
    if(ipv == 4){
        if(local->hasGlobalIPv4Address()){
            if(!tcpServer->listen(QHostAddress::AnyIPv4, this->port)){
                return;
            }
            qDebug() << "[ipv4 tcp]";
        }
    }
    if(ipv == 6){
        if(local->hasGlobalIPv6Address()){
                if(!tcpServer->listen(QHostAddress::AnyIPv6, this->port)){
                    return;
                }
                qDebug() << "[ipv6 tcp]";
            }
    }
    qDebug() << "[tcp server start listenning...]";
}
void TcpServer::whenClientDisconnect()
{
    qDebug() << "[client downline]";
    QTcpSocket *tcpSocket = static_cast<QTcpSocket *>(QObject::sender());
    tcpSocketList.removeOne(tcpSocket);
}

void TcpServer::whenClientSendDataToMe()
{
    QTcpSocket *tcpSocket = static_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = tcpSocket->readAll();
    qDebug() << "[tcp recv data from client]:" << data;
}
void TcpServer::whenNewConnection()
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


