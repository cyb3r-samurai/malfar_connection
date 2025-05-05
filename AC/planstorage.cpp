#include "planstorage.h"

PlanStorage::PlanStorage() {
    m_sector_plans = new std::map<int, SectorPlan>;
    m_data_chanels_plans  = new std::map<int, DataChanel>;
}

bool PlanStorage::changePlans(const std::map<int, SectorPlan> &new_sector_plan,
                              const std::map<int, DataChanel> &new_chanel_plan)
{
    m_lock.lockForWrite();
    *m_sector_plans =  new_sector_plan;
    *m_data_chanels_plans =  new_chanel_plan;
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

std::map<int, DataChanel> *PlanStorage::data_chanels_plans() const
{
    return m_data_chanels_plans;
}
