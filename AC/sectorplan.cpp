#include "sectorplan.h"

#include <QDebug>
#include <set>

SectorPlan::SectorPlan() {
 segment_plan  =new std::list<std::shared_ptr<SegmentPlan>>;
}

SectorPlan::~SectorPlan()
{
    delete	segment_plan;
}

void SectorPlan::append(std::shared_ptr<SegmentPlan> planPtr)
{
    segment_plan->push_back(planPtr);
    empty = false;
}

void SectorPlan::remove(std::shared_ptr<SegmentPlan> planPtr)
{
    segment_plan->remove(planPtr);
    empty = segment_plan->empty();
}

bool SectorPlan::validateSegment(std::shared_ptr<SegmentPlan> planPtr,
                                 const std::optional<std::list<std::shared_ptr<SegmentPlan>>>& dataToDelete)
{
    QDateTime start = planPtr->time_cel->time.front();
    QDateTime end = planPtr->time_cel->time.back();
    qDebug() << start<< end;
    auto it = segment_plan->begin();
    std::set<int>intersec_count;
    while (it != segment_plan->end()) {
        auto current_plan = it->get();
        QDateTime cur_start = current_plan->time_cel->time.front();
        QDateTime cur_end = current_plan->time_cel->time.back();
        qDebug() << cur_start << cur_end;
        if (((start >= cur_start) && (start <= cur_end)) ||
            ((end <= cur_end) && (end >= cur_start))     ||
            ((cur_start >= start) && (cur_start <= end)) ||
            ((cur_end <= end) && (cur_end >= cur_start))) {

            bool willBeDeleted = false;
            if(dataToDelete.has_value()) {
                auto dataToDeleteIt = dataToDelete.value().begin();
                while(dataToDeleteIt != dataToDelete.value().end()){
                    if (*dataToDeleteIt == *it) {
                        willBeDeleted = true;
                    }
                    ++dataToDeleteIt;
                }
            }
            if(!willBeDeleted) {
                intersec_count.insert(current_plan->data_chanel_number);
            }
        }
        ++it;
    }
    qDebug() << "Intersection count" << intersec_count.size();
    if (intersec_count.size() >= 6) {
        return false;
    }

    return true;
}

void SectorPlan::display_info()
{
    qDebug() << "Segments count in sector: " << segment_plan->size();
}

std::list<std::shared_ptr<SegmentPlan> > *SectorPlan::getSegment_plan()
{
    return segment_plan;
}
