#include "planfactory.h"
#include <QDebug>



PlanFactory::PlanFactory(PlanStorage *p_s, QObject *parent) :
    QObject{parent}, m_plan_storage{p_s}
{
    m_data_plans = p_s->data_chanels_plans();
    m_sector_plans = p_s->sector_plans();

    m_sector_vector = new std::vector<Sector>(4);
    m_sector_vector->at(0).set(1, 0, 900, 0, 900);
    m_sector_vector->at(1).set(2, 900, 1800, 0, 900);
    m_sector_vector->at(2).set(3, 1800, 2700, 0, 900);
    m_sector_vector->at(3).set(4, 2700, 3600, 0, 900);
}

int PlanFactory::createPlan(std::shared_ptr<Cel> cel_plan)
{
    struct PlanToAppend {
    public:
        std::shared_ptr<SegmentPlan> seg;
        int sector_number;
        int chanel_number;
    };
    std::list<PlanToAppend> plansToAppend;

    m_plan_storage->lockWrite();

    //clear data chanel
    if(cel_plan->m == 0) {
        m_data_plans->extract(cel_plan->chanel_number);
        auto sector_it = m_sector_plans->begin();
        while(sector_it != m_sector_plans->end()) {
            bool sector_erased = false;
            auto segments  = sector_it->second.getSegment_plan();
            auto segment_it = segments->begin();
            while(segment_it != segments->end()) {
                bool segment_erased = false;
                if(segment_it->get()->data_chanel_number == cel_plan->chanel_number) {
                    segments->erase(segment_it++);
                    segment_erased = true;
                    if(segments->size() == 0) {
                        qDebug() << "Планы сектора" << sector_it->first << "выполнены.";
                        m_sector_plans->erase(sector_it++);
                        sector_erased = true;
                    }
                }
                if(!segment_erased){
                    ++segment_it;
                }

            }
            if(!sector_erased){
                ++sector_it;
            }
        }
        qInfo() << "Очищены планы канала данных" << cel_plan->chanel_number;
        m_plan_storage->unloock();
        return 0;
    }

    int16_t a[2] = {cel_plan->cel[0][0], cel_plan->cel[0][1]};
    uint8_t sector_number = calculate_sector(a, *m_sector_vector);
    uint16_t lastCelIndex = cel_plan->m - 1;
    std::shared_ptr<SegmentPlan> segment_ptr = std::make_shared<SegmentPlan>();
    if(!(segment_ptr->initCel(cel_plan, sector_number, 0))) {
        return 255;
    }

    for(uint16_t i = 0;  i < cel_plan->m; ++i) {
        int16_t a[2] = {cel_plan->cel[i][0], cel_plan->cel[i][1]};
        uint8_t current_sector_number = calculate_sector(a, *m_sector_vector);

        //Если изменился сектор приема в плане, либо обрабатывется последние целеукозание, то
        //валидируется  полученный отрезок плана и добавляется в планы сектора и планы каналов данных.
        if(current_sector_number != sector_number) {
            bool chanel_status =
                (*m_data_plans)[cel_plan->chanel_number].validateSegment(segment_ptr);
            if (chanel_status) {
                bool sector_status =
                    (*m_sector_plans)[sector_number].validateSegment(segment_ptr);
                if (sector_status) {
                    segment_ptr->data_chanel_number = cel_plan->chanel_number;
                    segment_ptr->sector_number = sector_number;

                    PlanToAppend plan;
                    plan.seg = segment_ptr;
                    plan.sector_number = sector_number;
                    plan.chanel_number = cel_plan->chanel_number;
                    plansToAppend.push_back(plan);
                    auto new_ptr = std::make_shared<SegmentPlan>();
                    segment_ptr.reset();
                    segment_ptr = new_ptr;
                    segment_ptr->initCel(cel_plan, current_sector_number, i);
                    sector_number = current_sector_number;
                }
                else {
                    m_plan_storage->unloock();
                    return sector_number;
                }
            }
        }
        segment_ptr->appendCel(cel_plan);
  //      else {
            if(i == lastCelIndex) {
                bool chanel_status =
                    (*m_data_plans)[cel_plan->chanel_number].validateSegment(segment_ptr);
                if(chanel_status) {
                    bool sector_status =
                        (*m_sector_plans)[sector_number].validateSegment(segment_ptr);
                    if (sector_status) {
                        segment_ptr->sector_number = sector_number;
                        segment_ptr->data_chanel_number = cel_plan->chanel_number;

                        PlanToAppend plan;
                        plan.seg = segment_ptr;
                        plan.sector_number = sector_number;
                        plan.chanel_number = cel_plan->chanel_number;
                        plansToAppend.push_back(plan);

                        auto plans_to_append_it = plansToAppend.begin();
                        while(plans_to_append_it != plansToAppend.end()) {
                            (*m_sector_plans)[plans_to_append_it->sector_number].append(plans_to_append_it->seg);
                            (*m_data_plans)[plans_to_append_it->chanel_number].append(plans_to_append_it->seg);
                            ++plans_to_append_it;
                        }
                    }
                    else {
                        m_plan_storage->unloock();
                        return sector_number;
                    }
                }
            }
   //     }

       // segment_ptr->appendCel(cel_plan);
    }

    m_plan_storage->unloock();
    return 0;
}

void PlanFactory::clearPlans()
{
    qDebug() << "Clear data in plan factory";
    m_sector_plans->clear();
    m_data_plans->clear();

}

PlanFactory::~PlanFactory()
{

}

uint8_t PlanFactory::calculate_sector(int16_t* vec, const std::vector<Sector> &sector_vector)
{
    for(int i = 0; i < 4; i++) {
        if ((vec[0] >= sector_vector[i].az_start)&&(vec[0] <= sector_vector[i].az_end)) {
            return i+1;
            break;
        }
    }
    return 0;
}
