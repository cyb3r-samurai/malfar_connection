#ifndef REPORTDATA_H
#define REPORTDATA_H

#include <cstdint>

class ReportData
{
public:
    ReportData();
private:
    char reports[1100];
    uint32_t time;
};

#endif // REPORTDATA_H
