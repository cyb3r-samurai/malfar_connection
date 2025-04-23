#include "ac.h"


AC::AC(QObject *parent) :
    QObject{parent}
{
    m_session_factory = new SessionFactory;


    m_timer->start(1000);
    connect(m_timer, &QTimer::timeout, this, &AC::OnTimer);
}


void AC::OnCelRecieved(Cel& cel)
{
    m_scheduled_sessions_queue.push(m_session_factory->CreateSession(std::move(cel)));
}

void AC::OnTimer()
{
    std::unique_ptr<Session>& incoming_session
        = const_cast<std::unique_ptr<Session>&>(m_scheduled_sessions_queue.top());

    uint32_t current_time = seconds_since_epoch();
    if ((*incoming_session).getStart_time() < current_time) {
        // TODO:: Применить целеукозание
        m_started_sessions_queue.emplace(std::move(incoming_session));
        m_scheduled_sessions_queue.pop();
    }

}

uint32_t AC::seconds_since_epoch()
{
    QDateTime now = QDateTime::currentDateTime();
    QDateTime epoch(QDate(2000, 1, 1), QTime(0, 0, 0), Qt::UTC);
    qint64 time =  now.toSecsSinceEpoch();
    qint64 epoch_time = epoch.toSecsSinceEpoch();
    return time - epoch_time;
}
