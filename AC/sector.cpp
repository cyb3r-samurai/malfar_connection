#include "sector.h"

Sector::Sector() {}

void Sector::set(int number,int16_t az_s, int16_t az_e, int16_t angle_s, int16_t angle_e)
{
    sector_number = number;
    az_start = az_s;
    az_end = az_e;
    angle_start = angle_s;
    angle_end = angle_e;
}
