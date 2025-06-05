#include "cellstorage.h"

CellStorage::CellStorage(QObject *parent)
    : QObject{parent}
{}

void CellStorage::append(int16_t i_data, int16_t q_data)
{
    m_count++;
    m_i_data.push_back(i_data);
    m_q_data.push_back(q_data);
    if(m_count > 700) {
        Report data = toMessage();

        m_count = 0;
        m_i_data.clear();
        m_q_data.clear();

        emit ready_to_write(data);
    }
}

void CellStorage::set(quint8 data_chanel_number, quint8 ac_state, quint8 ka_number, QDateTime start_time, qint16 az[2])
{
    m_data_chanel_number = data_chanel_number;
    m_ac_state = ac_state;
    m_ka_number = ka_number;
    m_start_time = start_time;
    m_az[0] = az[0];
    m_az[1] = az[1];
    m_started = true;
    Q_ASSERT(m_count == 0);
}

void CellStorage::sendAll()
{
   // if ()
    Report data = toMessage();
    emit ready_to_write(data);
    m_count = 0;
    m_i_data.clear();
    m_q_data.clear();
}

quint32 CellStorage::size() const
{
    return m_count;
}

Report CellStorage::toMessage() const
{
    Report report(m_count);

    int min = 32000;
    int max = -32000;

    Q_ASSERT(m_i_data.size() == m_count);

    auto i_it = m_i_data.begin();
    auto q_it = m_q_data.begin();
    while(i_it != m_i_data.end()) {
        if (*i_it < min) min =  *i_it;
        if (*i_it > max) max =  *i_it;
        if (*q_it < min) min = *q_it;
        if (*q_it > max) max = *q_it;
        ++q_it;
        ++i_it;
    }
    int range = max - min;

    i_it = m_i_data.begin();
    q_it = m_q_data.begin();
    if (range != 0){
    for(quint32 i = 0; i < m_count; ++i, ++i_it, ++q_it ) {
        report.info[i][0] = *i_it / range * 256;
        report.info[i][1] = *q_it / range * 256;
    }
    }
    report.ac_state = m_ac_state;
    report.az[0] = m_az[0];
    report.az[1] = m_az[1];
    report.data_chanel_number = m_data_chanel_number;
    report.ka_number = m_ka_number;
    report.m = m_count;
    report.time = double(m_start_time.toSecsSinceEpoch()) / double(86400) + 25569;

    return report;
}

bool CellStorage::started() const
{
    return m_started;
}

void CellStorage::setTime()
{
    m_start_time = QDateTime::currentDateTime();
}

void CellStorage::finish()
{
    m_started = false;
}
