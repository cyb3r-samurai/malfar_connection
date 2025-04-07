#include "dsp.h"
#include <QDebug>

Dsp::Dsp() {}

bool Dsp::input(const QVector<double> &i_vec,
                const QVector<double> &q_vec, double period)
{
    ComplexVector in;
    in.resize(i_vec.size());
    for (int i = 0; i < i_vec.count(); i++) {
        in[i] = {i_vec[i], q_vec[i]};
    }

    makeVector(0, period, in.size(), _time);
    double fSamp = 1.0/period;
    makeVector(fSamp * -0.5,
               fSamp * (1.0/in.size()),
               in.size(),
               _freq);

    dftTransform(in, in);
    dftAmpDist(in, _amp);
    ampDistToDb(_amp, _ampDb);
    return true;
}

int Dsp::makeVector(double start, double step, int size, QVector<double> &out)
{
    out.resize(size);

    out[0] = start;
    for (int i =1; i < size; i++) {
        out[i] = out[i-1]+step;
    }
    return 0;

}

int Dsp::dftTransform(const ComplexVector &in, ComplexVector &out)
{
    int size = in.size();
   // size = 512;
    qDebug() << "size " << size;
    out.resize(size);

    auto x = new minfft_cmpl[size];
    //minfft_cmpl x[1000], y[1000];
    auto y = new minfft_cmpl[size];
    minfft_aux *a;
    a = minfft_mkaux_dft_1d(size);

    //cast ComplexVector to minfft_cmpl[]
    for (int i =0; i <size; i++) {
        x[i][0] = in[i].real();
        x[i][1] = in[i].imag();
    }

    minfft_dft(x, y, a);

    //cast minfft_cmpl[] to ComplexVector
    for (int i =0, iy = size/2;
         i <size; i++, iy++) {
        if(iy == size) iy = 0;
        out[i].real(y[iy][0]);
        out[i].imag(y[iy][1]);
    }

    minfft_free_aux(a);
    delete [] x;
    delete [] y;

    return 0;

}

int Dsp::dftAmpDist(const ComplexVector &in, QVector<double> &out)
{
    out.resize(in.size());

    for (int i =0; i < in.size() ; i++) {
        out[i] = std::abs(in[i]);
    }

    return 0;
}

int Dsp::ampDistToDb(const QVector<double> &in, QVector<double> &out)
{
    out.resize(in.size());

    for (int i = 0; i < in.size(); i++) {
        out[i] = 20 * log10(in[i]);
    }
    return 0;
}
