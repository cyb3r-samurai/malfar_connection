#include "datachanel.h"
#include <QDebug>

DataChanel::DataChanel() {}


bool DataChanel::append(std::shared_ptr<SegmentPlan> new_plan)
{
    QDateTime start = new_plan->time_cel->time.front();
    QDateTime end = new_plan->time_cel->time.back();

    auto it = m_segments.begin();
    while(it != m_segments.end()) {
        if (it->get()->time_cel->time.front() > end)
            break;
        ++it;
    }
    if(it == m_segments.end()) {
        m_segments.push_back(new_plan);
    }
    else{
        m_segments.insert(--it, new_plan);
    }
    empty = false;


    return true;
}

std::optional<std::list<std::shared_ptr<SegmentPlan> > > DataChanel::validateSegment(std::shared_ptr<SegmentPlan> new_plan)
{
    QDateTime start = new_plan->time_cel->time.front();
    QDateTime end = new_plan->time_cel->time.back();
    std::list<std::shared_ptr<SegmentPlan>> dataToDelete;
    auto it = m_segments.begin();

    while((it != m_segments.end()) /* || (it->get()->time_cel->time.front() > end)*/) {
        QDateTime current_start =  it->get()->time_cel->time.front();
        QDateTime current_end = it->get()->time_cel->time.back();

        if (((start >= current_start) && (start <= current_end)) ||
            ((end <= current_end) && (end >= current_start))     ||
            ((current_start >= start) && (current_start <= end)) ||
            ((current_end <= end) && (current_end >= current_start))) {

            dataToDelete.push_back(*it);
        }
        ++it;
    }

    if (dataToDelete.size() > 0) {
        return dataToDelete;
    }

    return std::nullopt;
}


bool DataChanel::pop()
{
    if(m_segments.size() > 0) {
        if(m_segments.size() == 1) {
            empty  = true;
        }
        m_segments.pop_front();
    }
    return true;
}

bool DataChanel::is_empty()
{
    return empty;
}

void DataChanel::clear()
{
    empty = true;
    m_segments.clear();
}

void DataChanel::remove(std::shared_ptr<SegmentPlan> ptr)
{
    m_segments.remove(ptr);
}


std::list<std::shared_ptr<SegmentPlan> > DataChanel::segments() const
{
    return m_segments;
}
