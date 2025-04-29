#include "datachanel.h"

DataChanel::DataChanel() {}

bool DataChanel::append(std::shared_ptr<SegmentPlan> new_plan)
{
    m_segments.push_back(new_plan);
    return true;
}

bool DataChanel::validateSegment(std::shared_ptr<SegmentPlan> new_plan)
{
    return true;
}
