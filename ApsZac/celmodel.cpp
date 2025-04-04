#include "celmodel.h"
#include <QDebug>

CelModel::CelModel(QObject *parent)
    : QObject{parent}
{
}

void CelModel::addKa(int kaNumber)
{
    CelData data;
    data.kaNumber = kaNumber;
    m_celitems.append(data);
    QVector<double> time;
    emit ka_added(kaNumber);
}

bool CelModel::exist(int kaNumber)
{
    if (m_celitems.isEmpty())
        return false;
    for(CelData &data: m_celitems){
        if(data.kaNumber == kaNumber) {
            return true;
        }
    }
    return false;
}

void CelModel::updateData(int kaNumber, QVector<double> &iData, QVector<double> &qData)
{
    for(qsizetype i = 0; i < m_celitems.count(); i++) {
        if (m_celitems[i].kaNumber == kaNumber) {
            m_celitems[i].iData.append(iData);
            m_celitems[i].qData.append(qData);
        }
    }
    emit dataUpdated(kaNumber);
}

CelData CelModel::getKaData(int kaNumber)
{
    CelData obj;

    for (qsizetype i = 0; i < m_celitems.count(); i++){
        if (m_celitems[i].kaNumber == kaNumber) {
            obj = m_celitems[i];
        }
    }

    return obj;
}

