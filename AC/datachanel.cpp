#include "datachanel.h"
#include <QDebug>

DataChanel::DataChanel() {}

bool DataChanel::append(std::shared_ptr<SegmentPlan> new_plan)
{
    m_segments.push_back(new_plan);
    empty = false;
    return true;
}

bool DataChanel::validateSegment(std::shared_ptr<SegmentPlan> new_plan)
{
    return true;
}

bool DataChanel::pop()
{
    if(m_segments.size() == 1 ) {
        m_segments.pop_front();
        empty = true;
    }
    return true;
}

bool DataChanel::is_empty()
{
    return empty;
}


std::list<std::shared_ptr<SegmentPlan> > DataChanel::segments() const
{
    return m_segments;
}
