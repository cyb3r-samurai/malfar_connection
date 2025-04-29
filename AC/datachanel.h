#ifndef DATACHANEL_H
#define DATACHANEL_H

#include "segmentplan.h"

#include <list>
#include <memory>


class DataChanel
{
public:
    DataChanel();
    bool append(std::shared_ptr<SegmentPlan> new_plan);
    bool validateSegment(std::shared_ptr<SegmentPlan> new_plan);

private:
    std::list<std::shared_ptr<SegmentPlan>> m_segments;
};

#endif // DATACHANEL_H
