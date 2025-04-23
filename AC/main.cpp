#include <QCoreApplication>
#include <TcpServer.h>
#include <dataserver.h>
#include <QFile>
#include <random>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpServer server(nullptr);

    return a.exec();
}
