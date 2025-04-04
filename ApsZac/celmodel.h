#ifndef CELMODEL_H
#define CELMODEL_H

#include "Message.h"

#include <QObject>


class CelModel : public QObject
{
    Q_OBJECT
public:
    explicit CelModel(QObject *parent = nullptr);

    void addKa(int kaNumber);
    bool exist(int kaNumber);
    void updateData(int kaNumber, QVector<double> &iData, QVector<double> &qData);
    CelData getKaData(int kaNumber);

signals:
    void ka_added(int);
    void dataUpdated(int);

private:
    QVector<CelData> m_celitems;
};

#endif // CELMODEL_H
