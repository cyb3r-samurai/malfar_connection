#include "planfactory.h"



PlanFactory::PlanFactory(std::map<int, DataChanel> *data_plans,
                         std::map<int, SectorPlan> *sector_plans) :
    m_data_plans{data_plans}, m_sector_plans{sector_plans}
{

}

bool PlanFactory::createPlan(std::shared_ptr<Cel> cel_plan)
{
    int16_t a[2] = {cel_plan->cel[0][0], cel_plan->cel[0][1]};
    uint8_t sector_number = calculate_sector(*a, m_sector_vector);

    std::shared_ptr<SegmentPlan> segment_ptr = std::make_shared<SegmentPlan>();
    segment_ptr->initCel(cel_plan, sector_number);
    for(int16_t i = 0;  i < cel_plan->m; ++i) {
        int16_t a[2] = {cel_plan->cel[i][0], cel_plan->cel[i][1]};
        uint8_t current_sector_number = calculate_sector(*a, m_sector_vector);

        //Если изменился сектор приема в плане, либо обрабатывется последние целеукозание, то
        //валидируется  полученный отрезок плана и добавляется в планы сектора и планы каналов данных.
        if((current_sector_number != sector_number) || (i == cel_plan->m-1)) {
            bool chanel_status =
                (*m_data_plans)[cel_plan->chanel_number].validateSegment(segment_ptr);
            if(!chanel_status) {
                int sector_status =
                    (*m_sector_plans)[current_sector_number].validateSegment(segment_ptr);
                if (sector_status == 0) {
                    (*m_sector_plans)[current_sector_number].append(segment_ptr);
                    (*m_data_plans)[cel_plan->chanel_number].append(segment_ptr);
                }
            }
            segment_ptr.reset();
            if(i != cel_plan->m-1) {
                segment_ptr = std::make_shared<SegmentPlan>();
                sector_number = current_sector_number;
                segment_ptr->initCel(cel_plan, sector_number);
            }
            else {
                break;
            }
        }

        segment_ptr->appendCel(cel_plan);
    }
    return true;
}
