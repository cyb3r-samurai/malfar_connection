// Класс управляет планми примема АС.
//TODO :: добавить класс шадулер с адекватным интерфейсом.

#ifndef AC_H
#define AC_H

#include "Message.h"
#include "datachanel.h"
#include "planfactory.h"
#include "sectorplan.h"
#include "planstorage.h"

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QThread>
#include <QDebug>
#include "pthread.h"
#include "sched.h"
#include "unistd.h"

#include <map>


class AC : public QObject
{
    Q_OBJECT
public:
    explicit AC(QObject* parent = nullptr);

    PlanStorage *plan_storage() const;

    PlanFactory *plan_factory() const;

signals:
    void plans_changed();
    void sector_plan_chanhed(const std::map<int, SectorPlan>&);
    void chanel_plan_chnaged(const std::map<int, DataChanel>&);
    void messageHandled(long long, quint8);

    void accept_cell(int data_chanel_number, int real_chanel_number, int sector,
                     const QDateTime& current_time, int ka_number, int az, int angle);
    void finish_data_chanel(int data_chanel_number, int real_chanal_number, int sector);
    void stopSending();
    void finish_segment(int data_chanel_number, int real_chanel_number, int sector);

public slots:
    void onStopRecieve(long long);
    void start();

private slots:
    void CheckTime();

private:
    // Планы приема по секторам
    std::map<int, SectorPlan>* m_sector_plans;

    // Каналы данных
    std::map<int, DataChanel>* m_chanel_plans;

    void startAtNextSecond();
    bool setAffinity(int cpuCore);

    QThread* m_plan_factory_thread;

    PlanFactory* m_plan_factory;
    PlanStorage* m_plan_storage;

    QTimer* m_timer;
};

#endif // AC_H
