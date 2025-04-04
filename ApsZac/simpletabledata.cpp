#include "simpletabledata.h"

SimpleTableData::SimpleTableData(QObject *parent)
    : QAbstractListModel{parent}
{
}

int SimpleTableData::rowCount(const QModelIndex &) const
{
    return m_rows->count();
}

int SimpleTableData::columnCount(const QModelIndex &parent) const
{
    return 10;
}

QVariant SimpleTableData::data(const QModelIndex &index, int role) const
{
    QVariant value;

    if(role == Qt::DisplayRole) {
        switch(index.column()) {
            case 0: {
                value = m_rows->at(index.row()).a;
                break;
            }
            case 1: {
                value = m_rows->at(index.row()).b;
                break;
            }
            case 2: {
                value = m_rows->at(index.row()).c;
                if (value.toInt() == 2) {
                    value = "Левая круговая";
                }
                break;
            }
            case 3: {
                uint32_t v = m_rows->at(index.row()).d;
                float f = (float)(*(float*)&v);
                value = f;
                break;
            }
            case 4: {
                value = secondsToDatetime(m_rows->at(index.row()).start_time).toString("yyyy-MM-dd hh:mm:ss");
                break;
            }
            case 5: {
                value = secondsToDatetime(m_rows->at(index.row()).end_time).toString("yyyy-MM-dd hh:mm:ss");
                break;
            }
            case 6: {
                value = m_rows->at(index.row()).first_c[0];
                break;
            }
            case 7: {
                value = m_rows->at(index.row()).first_c[1];
                break;
            }
            case 8: {
                value = m_rows->at(index.row()).last_c[0];
                break;
            }
            case 9: {
                value = m_rows->at(index.row()).last_c[1];
                break;
            }

        }
    }
    return value;
}

void SimpleTableData::populate()
{
//       int idx = m_rows->count();
//    this->beginInsertRows(QModelIndex(), 1, idx);
//    for (qsizetype i = 0; i < newValues->size(); i++){
//        m_rows->append(newValues->at(i));
//    }
//    endInsertRows();
    m_rows = new QList<SubSessionInfo>;
}

QVariant SimpleTableData::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Номер КА");
        case 1:
            return QString("Метка сеанса");
        case 2:
            return QString("Направление поляризации");
        case 3:
            return QString("Частота в кГц");
        case 4:
            return QString("Время начала сеанса");
        case 5:
            return QString("Время окончания сеанса");
        case 6:
            return QString("Первое ц. азимут");
        case 7:
            return QString("Первое ц. угол места");
        case 8:
            return QString("Последнее ц. азимут");
        case 9:
            return QString("Последнее ц. угол места");
        }
    }
    return QVariant();
}

void SimpleTableData::append(QList<SubSessionInfo> *newValues)
{
    int first_row =  m_rows->count() + 1;
    int last_row  = m_rows->count() + newValues->count();
    //if (m_rows->count() > 0) {
    //    beginRemoveRows(QModelIndex(), 1, m_rows->count());
    //    m_rows->clear();
    //    endRemoveRows();
    //}
    beginInsertRows(QModelIndex(), first_row, last_row);
    //m_rows->clear();
    for(qsizetype i = 0; i < newValues->count(); i++) {
        m_rows->append(newValues->at(i));
    }
    endInsertRows();
}

QDateTime SimpleTableData::secondsToDatetime(quint32 seconds) const
{
    QDateTime epoch(QDate(2000, 1, 1), QTime(0, 0, 0), Qt::UTC);
    return epoch.addSecs(seconds);
}


