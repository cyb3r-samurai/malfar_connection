#include "reportstatechecker.h"

ReportStateChecker::ReportStateChecker(PlanStorage *p_s, QObject *parent)
    : QObject{parent}, m_plan_storage{p_s}
{
//    m_timer = new QTimer();
//    connect(m_timer, &QTimer::timeout, this, &ReportStateChecker::onTimer);
}

void ReportStateChecker::onTimer()
{
    m_plan_storage->lockRead();
    m_data_chanel_plans = m_plan_storage->get_data_chanel_copy();
    m_plan_storage->unloock();
    //TODO:: получить телеметрию
    if(!m_data_chanel_plans.empty()) {
        create_recieve_state();
    }
}

void ReportStateChecker::onRequest(long long)
{
    //update data in class
    m_plan_storage->lockRead();
    m_data_chanel_plans = m_plan_storage->get_data_chanel_copy();
    m_plan_storage->unloock();

    //if(!m_data_chanel_plans.empty()) {
        create_session_info();
   // }
}

void ReportStateChecker::onAcStateRequest(long long)
{
    create_ac_state();
}

void ReportStateChecker::onStartingServer()
{
    create_ac_state();
}

void ReportStateChecker::create_ac_state()
{
    auto ac_state_ptr = std::make_shared<AcState>();
    emit acStateCreated(ac_state_ptr);
}

void ReportStateChecker::create_session_info()
{

    quint8 active_chanels_count = m_data_chanel_plans.size();

    auto sessionInfoPtr = std::make_shared<SessionInfo>();
    sessionInfoPtr->active_data_chanel_count = active_chanels_count;
    if (active_chanels_count != 0)
    sessionInfoPtr->m_chanel_data = new ChanelData[active_chanels_count];

    int chanel_mas_count = 0;
    auto plans_it = m_data_chanel_plans.begin();
    while (plans_it != m_data_chanel_plans.end()) {
        int chanel_number = plans_it->first;
        int segment_mas_count = 0;

        ChanelData *current_chanel =
            &(sessionInfoPtr->m_chanel_data[chanel_mas_count]);
        std::list<std::shared_ptr<SegmentPlan>> segments =
            m_data_chanel_plans[chanel_number].segments();

        current_chanel->chanel_number = chanel_number;
        current_chanel->segment_count = segments.size();
        current_chanel->segment_plan = new MessageSegmentPlan[segments.size()];
    //    for(int i = 0; i < segments.size(); ++i) {
    //        current_chanel->segment_plan[i] = new MessageSegmentPlan;
    //    }

        auto segment_it = segments.begin();
        while (segment_it != segments.end()) {
            auto current_segment = segment_it->get()->toMessage();
            qDebug() << "current segment debug";
            for(int i = 0; i < current_segment.m; i++) {
                qDebug() << i << current_segment.cel[i][0] << current_segment.cel[i][1];
            }
            current_chanel->segment_plan[segment_mas_count] = current_segment;
            ++segment_mas_count;
            ++segment_it;
        }
        ++chanel_mas_count;
        ++plans_it;
    }
    emit sessionInfoCreated(sessionInfoPtr);
}
void ReportStateChecker::create_recieve_state()
{
    auto recievedStatePtr = std::make_shared<RecieveState>();
    quint8 active_chanels_count = 0;
    std::for_each(m_data_chanel_plans.begin(), m_data_chanel_plans.end(), [&active_chanels_count](auto pair) {
        if(pair.second.active) {
            active_chanels_count++;
        }
    });

    //initializing recivestate
    recievedStatePtr->initializeChanelMas(active_chanels_count);
    recievedStatePtr->n = active_chanels_count;

    int chanel_mas_count = 0;

    //iterate over chanel plans and segments to form recivestate message
    auto plans_it = m_data_chanel_plans.begin();
    while(plans_it != m_data_chanel_plans.end()){
        if(plans_it->second.active){
        int chanel_number = plans_it->first;
        ChanelInfo *current_chanel =
            &(recievedStatePtr->chanel_mas[chanel_mas_count]);

        std::list<std::shared_ptr<SegmentPlan>> segments =
            m_data_chanel_plans[chanel_number].segments();

        auto segments_it = segments.begin();
        while(segments_it != segments.end()) {
            auto current_segment = segments_it->get();
            current_chanel->freq = current_segment->freq;
            current_chanel->ka_number = current_segment->ka_number;
            current_chanel->vec[0] = current_segment->current_az; // must be calculated
            current_chanel->vec[1] = current_segment->current_angle; // must be calculated
            current_chanel->real_chanel_number = current_segment->chanel_number;
            current_chanel->pol = current_segment->pol;
            current_chanel->signal_level = 1.125; // must be calculated
            current_chanel->sector_number = current_segment->sector_number;
            current_chanel->sector_state = 1; // must be calculated
            current_chanel->sector_start = current_segment->sector_start; // must be taken from sector plan
            current_chanel->sector_end = current_segment->sector_end; // must be taken from sector plan
            break;
        }
        }

        ++plans_it;
        ++chanel_mas_count;
    }
    emit reciveStateCreated(recievedStatePtr);
}
