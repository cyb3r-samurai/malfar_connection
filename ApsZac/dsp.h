#ifndef DSP_H
#define DSP_H

#include "minfft.h"

#include <QVector>
#include <complex>

class Dsp
{
public:
    Dsp();
    typedef std::complex<double> Complex;
    typedef QVector<Complex> ComplexVector;
    bool input(const QVector<double> & i_vec,
               const QVector<double>& q_vec, double period = 1./110.e3);

    int makeVector(double start, double step, int size, QVector<double> & out);

    int dftTransform(const ComplexVector & in, ComplexVector & out);
    int dftAmpDist(const ComplexVector & in, QVector<double> & out);
    int ampDistToDb(const QVector<double> & in, QVector<double> & out);

    const QVector<double> & ampDist() {return _amp;}
    const QVector<double> & freqVector() {return _freq;}
    const QVector<double> & ampDistDb() {return _ampDb;}
private:
    QVector<double> _amp;
    QVector<double> _ampDb;
    QVector<double> _time;
    QVector<double> _freq;
};

#endif // DSP_H
