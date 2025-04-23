#include "session.h"

Session::Session(Cel &&cel) :
    number{cel.number}, session_id{cel.sesssion_number},pol{cel.polarization}
{
    TimeCel a(10);
}

uint32_t Session::getStart_time() const
{
    return start_time;
}

uint32_t Session::getEnd_time() const
{
    return end_time;
}


TimeCel::TimeCel()
{

}

TimeCel::TimeCel(int n)
{

}
