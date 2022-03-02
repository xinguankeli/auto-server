#include <QCoreApplication>
#include <QDebug>
#include <QTextCodec>
#include "server/tcpserver.h"
#include "server/udpserver.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    TcpServer *tcpServer = new TcpServer(quint16(65534));
    tcpServer->listenning();
    UdpServer *udpServer = new UdpServer(quint16(65535));
    udpServer->listenning();
    qDebug() << "this is a auto server";
    return a.exec();
}
