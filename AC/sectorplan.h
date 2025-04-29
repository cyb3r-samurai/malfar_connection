#ifndef SECTORPLAN_H
#define SECTORPLAN_H

#include "segmentplan.h"

#include <vector>
#include <list>
#include <memory>
#include <map>

class SectorPlan
{
public:
    SectorPlan();
    void append(std::shared_ptr<SegmentPlan>);
    int validateSegment(std::shared_ptr<SegmentPlan>);

private:
    std::list<std::shared_ptr<SegmentPlan>>* segment_plan;
};

#endif // SECTORPLAN_H
