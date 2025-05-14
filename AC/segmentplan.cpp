#include "segmentplan.h"

SegmentPlan::SegmentPlan() {
    time_cel = new TimeCelDistribution;
}

void SegmentPlan::initCel(std::shared_ptr<Cel> celPtr, uint8_t sectorNumb)
{
    sector_number = sectorNumb;
    chanel_number = 0;
    pol =	celPtr->polarization;
    ka_number = celPtr->ka_number;
    start_time = celPtr->start_time;
    end_time = celPtr->end_time;
    m = celPtr->m;
 //   cel = celPtr->cel;
    delta = (end_time - start_time)/ double(m - 1);
    time_cel->time.push_back(start_time);
    time_cel->az.push_back(celPtr->cel[current_index][0]);
    time_cel->angle.push_back(celPtr->cel[current_index][1]);

    current_index++;
}

void SegmentPlan::appendCel(std::shared_ptr<Cel> celPtr)
{
    time_cel->time.push_back(start_time + current_index * delta);
    time_cel->az.push_back(celPtr->cel[current_index][0]);
    time_cel->angle.push_back(celPtr->cel[current_index][1]);

    current_index++;
}

MessageSegmentPlan SegmentPlan::toMessage()
{

}
