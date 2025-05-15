#include "logger.h"
#include <TcpServer.h>
#include <dataserver.h>

#include <QCoreApplication>
#include <QSettings>
#include <QFile>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setOrganizationName("NII_RTS");
    a.setOrganizationDomain("MyDomain");
    a.setApplicationName("AC");

    Logger* logger = new Logger;
    logger->installMsgHandler();
    TcpServer server(nullptr);

    return a.exec();
}
