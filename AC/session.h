#ifndef SESSION_H
#define SESSION_H

#include <cstdint>
#include "Message.h"

class TimeCel {
public:
    TimeCel();
    TimeCel(int n);
    int16_t * cel[2];
    uint32_t time;
};

class Session
{
public:
    Session(Cel&& cel);

    uint32_t getStart_time() const;
    uint32_t getEnd_time() const;

private:
    uint16_t number;
    int8_t session_id;
    int8_t pol;
    uint32_t freq;
    uint32_t start_time;
    uint32_t end_time;
    TimeCel *m_time_cel;
};

#endif // SESSION_H
