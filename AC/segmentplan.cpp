#include "segmentplan.h"

SegmentPlan::SegmentPlan() {
    time_cel = new TimeCelDistribution;
}

SegmentPlan::~SegmentPlan()
{
    delete time_cel;
}

bool SegmentPlan::initCel(std::shared_ptr<Cel> celPtr, uint8_t sectorNumb,uint8_t chanelNumber ,int index)
{
    sector_number = sectorNumb;
    data_chanel_number = chanelNumber;
    pol =	celPtr->polarization;
    ka_number = celPtr->ka_number;
    start_time = celPtr->start_time;
    end_time = celPtr->end_time;
    m = celPtr->m;
    current_index = index;
    id = celPtr->id;

    qint64 sec1 = (end_time - 25569) * 86400 * 1000;
    qint64 sec2 = (start_time - 25569) * 86400 * 1000;
     dt_time = QDateTime::fromMSecsSinceEpoch(sec2);

    delta = (end_time - start_time)/ double(m - 1);
    msec_delta = (sec1 - sec2)/ double(m-1);
    delta_dt = QDateTime::fromMSecsSinceEpoch(msec_delta);
    if (msec_delta < 1000) {
        return false;
    }

    return true;
}

void SegmentPlan::appendCel(std::shared_ptr<Cel> celPtr)
{
    time_cel->time.push_back(dt_time.addMSecs(msec_delta * current_index));
    time_cel->az.push_back(celPtr->cel[current_index][0]);
    time_cel->angle.push_back(celPtr->cel[current_index][1]);

    current_index++;
}

MessageSegmentPlan SegmentPlan::toMessage()
{
    MessageSegmentPlan msg;
    msg.sector_number = chanel_number;
    msg.pol = pol;
    msg.ka_number = ka_number;
    msg.freq = freq;
    msg.m = time_cel->time.size();

    quint64  sec = time_cel->time.front().toSecsSinceEpoch();
    msg.start_time =double(sec) / double (86400) + 25569;
    quint64  sec2 = time_cel->time.back().toSecsSinceEpoch();
    msg.end_time = double(sec2) / double (86400) + 25569;

    msg.cel = new int16_t *[time_cel->time.size()];
    for (int i = 0; i < msg.m; ++i) {
        msg.cel[i] = new int16_t[2];
    }
    auto angle_it = time_cel->angle.begin();
    auto az_it = time_cel->az.begin();


    int i = 0;
    while(angle_it != time_cel->angle.end()) {
        msg.cel[i][0] = *az_it;
        msg.cel[i][1] = *angle_it;
        ++i;
        ++az_it;
        ++angle_it;
    }


    return msg;

}
