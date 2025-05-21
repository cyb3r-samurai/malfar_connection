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
    ~SectorPlan();
    void append(std::shared_ptr<SegmentPlan> planPtr);
    bool validateSegment(std::shared_ptr<SegmentPlan> planPtr);
    void display_info();

    std::list<std::shared_ptr<SegmentPlan> > *getSegment_plan() ;

private:
    std::list<std::shared_ptr<SegmentPlan>>* segment_plan;
};

#endif // SECTORPLAN_H
