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
    tcpServer->listenning(4);
    UdpServer *udpServer = new UdpServer(quint16(65535));
    udpServer->listenning(4);
    return a.exec();
}
