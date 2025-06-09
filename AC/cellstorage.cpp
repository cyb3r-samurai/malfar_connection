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
        std::shared_ptr<Report> data = toMessage();

        m_count = 0;
        m_i_data.clear();
        m_q_data.clear();

        emit ready_to_write(data);
    }
}

void CellStorage::set(quint8 data_chanel_number, quint8 ac_state, quint8 ka_number, const QDateTime& start_time, qint16 az[2])
{
    m_data_chanel_number = data_chanel_number;
    m_ac_state = ac_state;
    m_ka_number = ka_number;
    double OADate2 = (start_time.toMSecsSinceEpoch() /86400000.0) + 25569.0;

    m_start_time = OADate2;
    m_az[0] = az[0];
    m_az[1] = az[1];
    m_started = true;
    Q_ASSERT(m_count == 0);
}

void CellStorage::sendAll()
{
   // if ()
    std::shared_ptr<Report> data = toMessage();
    emit ready_to_write(data);
    m_count = 0;
    m_i_data.clear();
    m_q_data.clear();
}

quint32 CellStorage::size() const
{
    return m_count;
}

std::shared_ptr<Report> CellStorage::toMessage() const
{
    auto report = std::make_shared<Report>(m_count);

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
            report->info[i][0] = std::round(( double(*i_it)  - min) * 255 / range  - 128);
            report->info[i][1] = std::round(( double(*q_it)  - min) * 255 / range  - 128);
            // if(i == m_count-1) {
            //     qDebug()<< i <<*i_it << *q_it<< report->info[i][0] << report->info[i][1] << min << max
            //              <<    (double(*i_it)  - min) * 255 / range  - 128;
            // }
    }
    }
    else {
        for(quint32 i = 0; i < m_count; ++i, ++i_it, ++q_it) {
            report->info[i][0] = *i_it;
            report->info[i][1] = *q_it;
        }
    }
    report->ac_state = m_ac_state;
    report->az[0] = m_az[0];
    report->az[1] = m_az[1];
    report->data_chanel_number = m_data_chanel_number;
    report->ka_number = m_ka_number;
    report->m = m_count;
    report->time = m_start_time;

    return report;
}

bool CellStorage::started() const
{
    return m_started;
}

void CellStorage::setTime(double time)
{
    m_start_time = time;
}

void CellStorage::finish()
{
    m_started = false;
}

quint8 CellStorage::getDataChanel()
{
    return m_data_chanel_number;
}
