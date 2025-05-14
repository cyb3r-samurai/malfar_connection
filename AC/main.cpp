#include <QCoreApplication>
#include <QSettings>
#include <TcpServer.h>
#include <dataserver.h>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setOrganizationName("NII_RTS");
    a.setOrganizationDomain("MyDomain");
    a.setApplicationName("AC");

    TcpServer server(nullptr);

    return a.exec();
}
