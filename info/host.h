#ifndef HOST_H
#define HOST_H

#include <QObject>
#include <QString>
#include <QList>
//该类是用来获取此台计算机的信息的
class host : public QObject
{
    Q_OBJECT
public:
    explicit host(QObject *parent = nullptr);
private:
    QList<QString> IPv6Address;
    //set get
public:
    void setIPv6Address(QList<QString> address);
    QList<QString> getIPv6Address();
    //判断是否有IPv6的地址
    bool hasGlobalIPv6Address();
};

#endif // HOST_H
