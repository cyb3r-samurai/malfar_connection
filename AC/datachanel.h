#ifndef DATACHANEL_H
#define DATACHANEL_H

#include "segmentplan.h"

#include <list>
#include <optional>
#include <memory>



class DataChanel
{
public:
    DataChanel();
    bool append(std::shared_ptr<SegmentPlan> new_plan);

    auto validateSegment(std::shared_ptr<SegmentPlan> new_plan)
        ->std::optional<std::list<std::shared_ptr<SegmentPlan>>>;
    bool pop();
    bool is_empty();
    int size();
    void clear();
    void remove(std::shared_ptr<SegmentPlan>);
    bool active = false;

    std::list<std::shared_ptr<SegmentPlan> > segments() const;

private:
    bool empty = true;
    std::list<std::shared_ptr<SegmentPlan>> m_segments;
};

#endif // DATACHANEL_H
