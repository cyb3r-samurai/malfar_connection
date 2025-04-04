#ifndef SIMPLETABLEDATA_H
#define SIMPLETABLEDATA_H

#include <Message.h>
#include <QAbstractTableModel>
#include <QObject>
#include <QVariant>
#include <QDateTime>


class SimpleTableData : public QAbstractListModel
{
public:
    explicit SimpleTableData(QObject *parent = nullptr);
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void populate();
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void append(QList<SubSessionInfo> *newValues);
private:
    QList<SubSessionInfo> *m_rows;

    QDateTime secondsToDatetime(quint32 seconds) const;
};

#endif // SIMPLETABLEDATA_H
