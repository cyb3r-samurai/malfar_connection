#ifndef SECTOR_H
#define SECTOR_H

#include <sectorplan.h>

#include <cstdint>

class Sector
{
public:
    Sector();

    int sector_number;

// Границы сектора азимут[start; end], угло места[start;end]
    int16_t az_start;
    int16_t az_end;
    int16_t angle_start;
    int16_t angel_end;

private:
};

#endif // SECTOR_H
