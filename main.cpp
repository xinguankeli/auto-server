#include <QCoreApplication>
#include <QDebug>
#include <QTextCodec>
#include "server/server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    Server *server = new Server(quint16(65534));
    return a.exec();
}
