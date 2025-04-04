#include <QCoreApplication>
#include <QtTest/QTest>
#include <TcpServer.h>
#include <QFile>
#include <QRegularExpression>
#include <QValidator>
#include <random>

QPair<double, double> parse(QString const &str) {
    QString buffer = str;

    buffer.remove('e');
    buffer.remove('i');

    //{+|-}double1{+|-}int1{+|-}double2{+|-}int2
    int Ix = -1;
    while (true) {
        Ix = buffer.indexOf(QRegularExpression("[+-]"), Ix+2);
        if (Ix == -1) break;
        buffer.insert(Ix, ':');
    }
    //:{+|-}double1:{+|-}int1:{+|-}double2:{+|-}int2
    QStringList list = buffer.split(':', Qt::SkipEmptyParts);
    //TODO need test

 //   if ( list.size() != 4 ) return;

    double reDbl = list[0].toDouble()*pow(10, list[1].toDouble()+7);
    double imDbl = list[2].toDouble()*pow(10, list[3].toDouble()+7);

    return qMakePair(reDbl, imDbl);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    TcpServer server(nullptr);
    return a.exec();
}
