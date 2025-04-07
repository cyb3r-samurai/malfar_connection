#include "timeplotter.h"

TimePlotter::TimePlotter(QCustomPlot* plotter, QObject *parent) : QObject(parent)
{
    this->plot = plotter;

    iGraph =  plot->addGraph(plot->xAxis, plot->yAxis);
    qGraph = plot->addGraph(plot->xAxis, plot->yAxis);
    iGraph->setPen(QPen(Qt::blue));
    qGraph->setPen(QPen(Qt::red));
    plot->xAxis->setLabel("t");
    plot->yAxis->setLabel("I/Q");
   // plot->yAxis2->setLabel("Q");
   // plot->yAxis2->setVisible(true);
    plot->setInteractions(QCP::iRangeDrag |
                          QCP::iRangeZoom);



}
void TimePlotter::setIData(const QVector<double> &time, const QVector<double> &i)
{
    iGraph->setData(time, i);
    if (useAutRescale)
       iGraph->rescaleAxes();


    plot->replot();
}

void TimePlotter::setQData(const QVector<double> &time, const QVector<double> &q)
{
    if(q.count() != time.count()) {
        qDebug() << "Size error in  qdata";
    }
    qDebug() << "time sample " << time[3];
    qDebug() << "qdata sample" << q[3];
    qGraph->setData(time,q);
    qGraph->rescaleAxes();

    plot->replot();
}

void TimePlotter::autoRescaleEnable(bool en)
{
    useAutRescale = en;
}
