#include "reportstatechecker.h"

ReportStateChecker::ReportStateChecker(PlanStorage *p_s, QObject *parent)
    : QObject{parent}, m_plan_storage{p_s}
{
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &ReportStateChecker::onTimer);
}

void ReportStateChecker::onTimer()
{
    m_plan_storage->lockRead();
    m_data_chanel_plans = m_plan_storage->data_chanels_plans();
    m_plan_storage->unloock();

    //TODO:: получить телеметрию
    create_recieve_state();
}

void ReportStateChecker::create_recieve_state()
{
    std::shared_ptr<RecieveState> recievedStatePtr = std::make_shared<RecieveState>();
    int active_chanels_count = m_data_chanel_plans->size();
    recievedStatePtr->n = active_chanels_count;
    for (int i = 1; i <= active_chanels_count; ++i) {
        ChanelInfo *current_chanel = &(recievedStatePtr->chanel_mas[i]);
        auto it = (*m_data_chanel_plans)[i].segments().begin();
        while(it !=(*m_data_chanel_plans)[i].segments().end()) {
            current_chanel->freq = it->get()->freq;
            current_chanel->ka_number = it->get()->ka_number;
            current_chanel->vec[0] = 123; // must be calculated
            current_chanel->vec[1] = 123; // must be calculated
            current_chanel->real_chanel_number = it->get()->chanel_number;
            current_chanel->pol = it->get()->pol;
            current_chanel->signal_level = 0; // must be calculated
            current_chanel->sector_number = it->get()->sector_number;
            current_chanel->sector_state = 0; // must be calculated
            current_chanel->sector_start = 0;
            current_chanel->sector_end = 0;
            ++it;
        }
    }
}
