#ifndef AC_H
#define AC_H

#include "sector.h"
#include "session.h"
#include "Message.h"
#include "sessionfactory.h"

#include <QObject>
#include <QTimer>
#include <QDateTime>

#include <queue>
#include <vector>

class AC : public QObject
{
    Q_OBJECT
public:
    explicit AC(QObject* parent = nullptr);

public slots:
    void OnCelRecieved(Cel&);
    void OnTimer();

private:
    struct cmp_start_time {
        bool operator()(const std::unique_ptr<Session>& first,
                        const std::unique_ptr<Session>& second) {
            return (*first).getStart_time() < (*second).getStart_time();
        };
    };

    struct cmp_end_time {
        bool operator()(const std::unique_ptr<Session>& first,
                        const std::unique_ptr<Session>& second) {
            return (*first).getEnd_time() > (*second).getEnd_time();
        };
    };
    QTimer* m_timer;
    Sector sec_mas[4];
    std::priority_queue<std::unique_ptr<Session>,
                        std::vector<std::unique_ptr<Session>>,
                        cmp_start_time> m_scheduled_sessions_queue;

    std::priority_queue<std::unique_ptr<Session>,
                        std::vector<std::unique_ptr<Session>>,
                        cmp_end_time> m_started_sessions_queue;


    SessionFactory* m_session_factory;

    uint32_t seconds_since_epoch();
};

#endif // AC_H
