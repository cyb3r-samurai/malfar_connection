#ifndef TIMEPLOTTER_H
#define TIMEPLOTTER_H

#include <qcustomplot.h>
#include <QObject>

class TimePlotter : public QObject
{
    Q_OBJECT
public:

    explicit TimePlotter(QCustomPlot *plotter, QObject *parent = nullptr);
    QCustomPlot *plot;
    QCPGraph* iGraph;
    QCPGraph* qGraph;
    bool useAutRescale = false;

public slots:
    void setIData(const QVector<double> &time, const QVector<double> &i);
    void setQData(const QVector<double> &time, const QVector<double> &q);
    void autoRescaleEnable(bool en);
signals:

private:
};

#endif // TIMEPLOTTER_H
