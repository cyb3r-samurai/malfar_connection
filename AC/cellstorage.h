#ifndef CELLSTORAGE_H
#define CELLSTORAGE_H

#include "Message.h"

#include <QObject>
#include <QDebug>
#include <QDateTime>

#include <list>

class CellStorage : public QObject
{
    Q_OBJECT
public:
    explicit CellStorage(QObject *parent = nullptr);
    void append(int16_t i_data, int16_t q_data);
    void set(quint8 data_chanel_number, quint8 ac_state,
             quint8 ka_number, QDateTime start_time,
             qint16 az[2]);
    void sendAll();
    quint32 size() const;
    Report toMessage() const;
    bool started() const;
    void setTime();
    void finish();

signals:
    void ready_to_write(Report&);

private:
    quint8 m_data_chanel_number;
    quint8 m_ac_state;
    quint8 m_ka_number;
    QDateTime m_start_time;
    qint16 m_az[2];
    quint32 m_count = 0;
    std::list<int16_t>  m_i_data;
    std::list<int16_t>  m_q_data;

    bool m_started = false;

};

#endif // CELLSTORAGE_H
