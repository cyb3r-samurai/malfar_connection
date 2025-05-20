#include "sectorplan.h"

#include <QDebug>

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
}

int SectorPlan::validateSegment(std::shared_ptr<SegmentPlan> planPtr)
{
    return 0;
}

void SectorPlan::display_info()
{
    qDebug() << "Segments count in sector: " << segment_plan->size();
}

std::list<std::shared_ptr<SegmentPlan> > *SectorPlan::getSegment_plan()
{
    return segment_plan;
}
