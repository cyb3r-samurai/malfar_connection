#ifndef SECTORPLAN_H
#define SECTORPLAN_H

#include "segmentplan.h"

#include <vector>
#include <list>
#include <memory>
#include <map>
#include <optional>

class SectorPlan
{
public:
    SectorPlan();
    ~SectorPlan();
    void append(std::shared_ptr<SegmentPlan> planPtr);
    void remove(std::shared_ptr<SegmentPlan> planPtr);
    bool validateSegment(std::shared_ptr<SegmentPlan> planPtr,
                         const std::optional<std::list<std::shared_ptr<SegmentPlan>>>& dataToDelet);
    void display_info();
    bool is_empty() { return empty; };

    std::list<std::shared_ptr<SegmentPlan> > *getSegment_plan() ;

private:
    bool empty = true;
    std::map<int, int> m_real_chanel_map;
    std::list<std::shared_ptr<SegmentPlan>>* segment_plan;
};

#endif // SECTORPLAN_H
