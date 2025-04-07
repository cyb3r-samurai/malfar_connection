#include <QCoreApplication>
#include <QtTest/QTest>
#include <TcpServer.h>
#include <QFile>
#include <QRegularExpression>
#include <QValidator>
#include <random>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
/*
    Dsp dsp;
    QVector<double> i_vec;
    QVector<double> q_vec;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-127, 128);
    for (qsizetype i =0; i < 1000; i++) {
        c_pair data;
        data.I = dist(rng);
        data.Q = dist(rng);
        double temp = data.I;
        double tempq = data.Q;
        i_vec.append(temp/127);
        q_vec.append(tempq/127);
    }

    dsp.input(i_vec, q_vec);
    */

    TcpServer server(nullptr);
    return a.exec();
}
