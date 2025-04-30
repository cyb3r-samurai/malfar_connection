#include "planstorage.h"

PlanStorage::PlanStorage() {
    m_sector_plans = new std::map<int, SectorPlan>;
}

bool PlanStorage::changePlans(const std::map<int, SectorPlan> &new_plan)
{
    m_lock.lockForWrite();
    *m_sector_plans =  new_plan;
    m_lock.unlock();
    return true;
}

std::map<int, SectorPlan> *PlanStorage::sector_plans() const
{
    return m_sector_plans;
}

bool PlanStorage::lockRead()
{
    m_lock.lockForRead();
    return true;
}

bool PlanStorage::unloock()
{
    m_lock.unlock();
    return true;
}
