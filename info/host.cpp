#include "host.h"
#include <QHostInfo>
#include <QHostAddress>
#include <QList>
#include <QDebug>
#include <QNetworkInterface>
host::host(QObject *parent)
    : QObject{parent}
{
    //临时存放地址变量
    QList<QString> IPv6AddressList;
    //根据主机名获取主机的地址列表
//    QList<QHostAddress> ipv6Address = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
    QList<QHostAddress> ipv6Address =  QNetworkInterface::allAddresses();
    //遍历列表
    if(ipv6Address.size() > 0){
        foreach(QHostAddress add, ipv6Address){
            //如果是IPv6协议
            if(add.protocol() == QAbstractSocket::IPv6Protocol){
                //如果是全球唯一地址
                if(add.isGlobal()){
                    IPv6AddressList.append(add.toString());
                }
            }
        }
    }
    QList<QString> IPv4AddressList;
//    QList<QHostAddress> ipv4Address = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
    QList<QHostAddress> ipv4Address = QNetworkInterface::allAddresses();
    if(ipv4Address.size() > 0){
        foreach(QHostAddress add, ipv4Address){
            if(add.protocol() == QAbstractSocket::IPv4Protocol){
                if(add.isGlobal()){
                    IPv4AddressList.append(add.toString());
                }
            }
        }
    }

    if(!IPv6AddressList.isEmpty()){
        //将获取到的地址存放到类的变量里
        this->setIPv6Address(IPv6AddressList);
        qDebug() << "[get IPv6 address successful]";
    }else{
        qDebug() << "[get IPv6 address error]";
    }
    if(!IPv4AddressList.isEmpty()){
        this->setIPv4Address(IPv4AddressList);
        qDebug() << "[get IPv4 address successful]";
    }else{
        qDebug() << "[get IPv4 address error]";
    }
}

void host::setIPv6Address(QList<QString> address)
{
    this->IPv6Address = address;
}

QList<QString> host::getIPv6Address()
{
    return this->IPv6Address;
}

void host::setIPv4Address(QList<QString> address)
{
    this->IPv4Address = address;
}

QList<QString> host::getIPv4Address()
{
    return this->IPv4Address;
}

bool host::hasGlobalIPv6Address()
{
    if(!this->IPv6Address.isEmpty()){
        return true;
    }
    return false;
}

bool host::hasGlobalIPv4Address()
{
    if(!this->IPv4Address.isEmpty()){
        return true;
    }
    return false;
}
