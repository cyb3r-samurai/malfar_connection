#include "logger.h"
#include <TcpServer.h>
#include <dataserver.h>

#include <QCoreApplication>
#include <QObject>
#include <QSettings>
#include <QFile>


int main(int argc, char *argv[])
{
    QCoreApplication* a = new QCoreApplication(argc, argv);
    a->setOrganizationName("NII_RTS");
    a->setOrganizationDomain("MyDomain");
    a->setApplicationName("AC");

    Logger* logger = new Logger;
    logger->installMsgHandler();

    TcpServer* server = new TcpServer(QCoreApplication::instance());
    int ret  = a->exec();
    return ret;
    qDebug() << "closing app";
}
