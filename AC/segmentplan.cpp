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

    qint64 sec1 = (end_time - 25569) * 86400 * 1000;

    qint64 sec2 = (start_time - 25569) * 86400 * 1000;
    QDateTime dt_time = QDateTime::fromMSecsSinceEpoch(sec2);

    delta = (end_time - start_time)/ double(m - 1);
    msec_delta = (sec1 - sec2)/ double(m-1);
    delta_dt = QDateTime::fromMSecsSinceEpoch(msec_delta);

    time_cel->time.push_back(dt_time);
    time_cel->az.push_back(celPtr->cel[current_index][0]);
    time_cel->angle.push_back(celPtr->cel[current_index][1]);

    current_index++;
}

void SegmentPlan::appendCel(std::shared_ptr<Cel> celPtr)
{
    time_cel->time.push_back(time_cel->time.back().addMSecs(msec_delta));
    time_cel->az.push_back(celPtr->cel[current_index][0]);
    time_cel->angle.push_back(celPtr->cel[current_index][1]);

    current_index++;
}

MessageSegmentPlan SegmentPlan::toMessage()
{

}
