#include "dftplotter.h"

DftPlotter::DftPlotter(QCustomPlot* plotter, QObject *parent)
    : QObject{parent}
{
    this->plot = plotter;
    ampDistGraph = plot->addGraph();
    plot->xAxis->setLabel("f, Гц");
    plot->yAxis->setLabel("дБ");
    plot->setInteractions(QCP::iRangeDrag |
                          QCP::iRangeZoom | QCP::iSelectPlottables);
    ampDistGraph->setSelectable(QCP::stSingleData);
}

void DftPlotter::autoRescaleEnable(bool en)
{
    useAutRescale = en;
}

void DftPlotter::setAmpDistData(const QVector<double> &freq, const QVector<double> &amp)
{
    ampDistGraph->setData(freq, amp);
    if (useAutRescale) ampDistGraph->rescaleAxes();
    plot->replot();
}

