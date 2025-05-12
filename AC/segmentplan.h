#ifndef SEGMENTPLAN_H
#define SEGMENTPLAN_H

#include "Message.h"

#include <cstdint>
#include <vector>
#include <memory>

struct TimeCelDistribution
{
    std::vector<int16_t> az;
    std::vector<int16_t> angle;
    std::vector<double> time;
};

class SegmentPlan
{
public:
    SegmentPlan();

    uint8_t sector_number; // 1, 2, 3, 4
    uint8_t chanel_number; // номер физического канала приема
    uint8_t pol; // 1 - правая круговая
                 // 2 - левая круговая
                 // 3 - вертикальная
                 // 4 - горизонтальная
                 // 5 - линейная + 45 град
                 // 6 - линейна - 45 град
    uint16_t ka_number;
    uint32_t freq;
    double start_time;
    double end_time;
    uint16_t m;
    int16_t** cel;

    TimeCelDistribution* time_cel;
    uint16_t current_index = 0;
    double delta;

    void initCel(std::shared_ptr<Cel> cel, uint8_t sector_number);
    void appendCel(std::shared_ptr<Cel> cel);
    MessageSegmentPlan toMessage();
};

#endif // SEGMENTPLAN_H
