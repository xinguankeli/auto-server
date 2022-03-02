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

void UdpServer::listenning()
{
    if(local->hasGlobalIPv6Address()){
        if(!udpSocket->bind(QHostAddress::AnyIPv6, this->port)){
            return;
        }
        qDebug() << "[ipv6 udp]";
    }else if(local->hasGlobalIPv4Address()){
        if(!udpSocket->bind(QHostAddress::AnyIPv4, this->port)){
            return;
        }
        qDebug() << "[ipv4 udp]";
    }else{
        qDebug() << "[udp server start error]";
    }
    qDebug() << "[udp server start listenning...]";
}

void UdpServer::whenClientSendDataTome()
{
    QByteArray array;
    while(udpSocket->hasPendingDatagrams()){
        array.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(array.data(), array.size());
        qDebug() << "udp server recive data:" << QString::fromUtf8(array);
    }
}
