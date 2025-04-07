#ifndef DFTPLOTTER_H
#define DFTPLOTTER_H

#include <qcustomplot.h>

#include <QObject>

class DftPlotter : public QObject
{
    Q_OBJECT
public:
    explicit DftPlotter(QCustomPlot *plotter, QObject *parent = nullptr);
    void autoRescaleEnable(bool en);
    void setAmpDistData(const QVector<double>& freq, const QVector<double> &amp);

signals:

private:
    QCustomPlot* plot;
    QCPGraph* ampDistGraph;
    bool useAutRescale = true;
};

#endif // DFTPLOTTER_H
