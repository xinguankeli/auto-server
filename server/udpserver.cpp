#include "udpserver.h"
#include <QDebug>
UdpServer::UdpServer(quint16 port)
{
    this->port = port;
    local = new Host();
    udpSocket = new QUdpSocket();
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(whenClientSendDataTome()));
}

UdpServer::~UdpServer()
{
    if(udpSocket->isOpen()){
        udpSocket->close();
    }
    delete local;
    deleteLater();
}

void UdpServer::listenning(int ipv)
{
    if( ipv != 4 && ipv != 6){
        qDebug() << "[ip version error]";
        return;
    }
    if(ipv == 4){
        if(local->hasGlobalIPv4Address()){
            if(!udpSocket->bind(QHostAddress::AnyIPv4, this->port)){
                return;
            }
            qDebug() << "[ipv4 udp]";
        }
    }else if(ipv == 6){
        if(local->hasGlobalIPv6Address()){
            if(!udpSocket->bind(QHostAddress::AnyIPv6, this->port)){
                return;
            }
            qDebug() << "[ipv6 udp]";
        }
    }
    qDebug() << "[udp server start listenning...]";
}

void UdpServer::whenClientSendDataTome()
{
    QByteArray array;
    while(udpSocket->hasPendingDatagrams()){
        array.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(array.data(), array.size());
        qDebug() << "[udp recv data from client]:" <<array;
    }
}
