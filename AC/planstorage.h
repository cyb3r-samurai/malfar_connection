#ifndef PLANSTORAGE_H
#define PLANSTORAGE_H

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
    bool changePlans(const std::map<int, SectorPlan>& new_plan);

    std::map<int, SectorPlan> *sector_plans() const;
    bool lockRead();
    bool unloock();

private:
    std::map<int, SectorPlan>* m_sector_plans;
    QReadWriteLock m_lock;
};

#endif // PLANSTORAGE_H
