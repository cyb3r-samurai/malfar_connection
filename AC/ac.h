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

#include <map>


class AC : public QObject
{
    Q_OBJECT
public:
    explicit AC(QObject* parent = nullptr);

    PlanStorage *plan_storage() const;

signals:
    void SessionStarted(int , int);
    void SessionEnd(int, int);
    void plans_changed();
    void sector_plan_chanhed(const std::map<int, SectorPlan>&);
    void chanel_plan_chnaged(const std::map<int, DataChanel>&);
    void messageHandled(long long, quint8);

public slots:
    void OnCelRecieved(std::shared_ptr<Cel> cel, long long);
    void onStopRecieve(long long);

private slots:
    void CheckTime();

private:
    // Планы приема по секторам
    std::map<int, SectorPlan>* m_sector_plans;

    // Каналы данных
    std::map<int, DataChanel>* m_chanel_plans;

    void startAtNextSecond();

    QThread* m_plan_factory_thread;

    PlanFactory* m_plan_factory;
    PlanStorage* m_plan_storage;

    QTimer* m_timer;
};

#endif // AC_H
