// Валедирует и создает план слежения.
// Если план не валидный выдает std::nullopt

#ifndef PLANFACTORY_H
#define PLANFACTORY_H

#include "datachanel.h"
#include "Message.h"
#include "segmentplan.h"
#include "sector.h"
#include "sectorplan.h"
#include "planstorage.h"

#include <memory>
#include <vector>
#include <optional>
#include <map>
#include <set>

#include <QThread>
#include <QObject>

#include <cstdint>


class PlanFactory : public QObject
{
    Q_OBJECT
public:
    explicit PlanFactory(PlanStorage* p_s, QObject* parent = nullptr);
    int createPlan(std::shared_ptr<Cel> cel);

    void clearPlans();

    virtual ~PlanFactory();

public slots:
    void onPlanRecieved(std::shared_ptr<Cel>, long long);
    void onP2SocketStateChanging(bool);

signals:
    void messageHandled(long long, quint8);
    void stopDataChanel(quint8);
    void stopSegment(quint8 chanel_number, quint8 real_chanel_number, quint8 sector);

private:
    bool p2_connected = false;
    PlanStorage * m_plan_storage;
    std::map<int, DataChanel>* m_data_plans;
    std::map<int, SectorPlan>* m_sector_plans;
    std::vector<Sector>* m_sector_vector;
    uint8_t calculate_sector(int16_t* vec, const std::vector<Sector>& sector_vector);
    double getTime() const;

    bool check_data(std::shared_ptr<Cel> cel) const;

};

#endif // PLANFACTORY_H
