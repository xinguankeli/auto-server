#include "host.h"
#include <QHostInfo>
#include <QHostAddress>
#include <QList>
#include <QDebug>
host::host(QObject *parent)
    : QObject{parent}
{
    //临时存放地址变量
    QList<QString> IPv6AddressList;
    //根据主机名获取主机的地址列表
    QList<QHostAddress> address = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
    //遍历列表
    foreach(QHostAddress add, address){
        //如果是IPv6协议
        if(add.protocol() == QAbstractSocket::IPv6Protocol){
            //如果是全球唯一地址
            if(add.isGlobal()){
                IPv6AddressList.append(add.toString());
            }
        }
    }
    if(!IPv6AddressList.isEmpty()){
        //将获取到的地址存放到类的变量里
        this->setIPv6Address(IPv6AddressList);
        qDebug() << "[获取IPv6地址成功]";
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

bool host::hasGlobalIPv6Address()
{
    if(!this->IPv6Address.isEmpty()){
        return true;
    }
    return false;
}
