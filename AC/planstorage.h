#ifndef PLANSTORAGE_H
#define PLANSTORAGE_H

#include "datachanel.h"
#include "sectorplan.h"
#include "segmentplan.h"

#include <QReadWriteLock>

#include <map>
#include <list>
#include <memory>

class PlanStorage
{
public:
    PlanStorage();
    bool changePlans(const std::map<int, SectorPlan>& new_sector_plan ,
                     const std::map<int, DataChanel>& new_chanel_plan);

    std::map<int, SectorPlan> *sector_plans() const;
    std::map<int, DataChanel> *data_chanels_plans() const;

    bool lockRead();
    bool unloock();
private:
    std::map<int, SectorPlan>* m_sector_plans;
    std::map<int, DataChanel>* m_data_chanels_plans;
    QReadWriteLock m_lock;
};

#endif // PLANSTORAGE_H
