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
    std::optional<std::list<std::shared_ptr<SegmentPlan>>> dataToDelete;
    bool first_assign = true;

    m_plan_storage->lockWrite();


    if(!check_data(cel_plan)) {
        m_plan_storage->unloock();
        return 255;
    }

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
        emit stopDataChanel(cel_plan->chanel_number);
        m_plan_storage->unloock();
        return 0;
    }

    int16_t a[2] = {cel_plan->cel[0][0], cel_plan->cel[0][1]};
    uint8_t sector_number = calculate_sector(a, *m_sector_vector);

    uint16_t lastCelIndex = cel_plan->m - 1;
    std::shared_ptr<SegmentPlan> segment_ptr = std::make_shared<SegmentPlan>();
    if (sector_number == 0) {
        qInfo() << "Неверные целеуказания";
        m_plan_storage->unloock();
        return 255;
    }
    else {
        if((sector_number > 1) &&(sector_number < 5)) {
            qInfo() <<  "Сектор" << sector_number<<"не доступен.";
            m_plan_storage->unloock();
            return sector_number;
        }
    }

    if(!(segment_ptr->initCel(cel_plan, sector_number,cel_plan->chanel_number, 0
                               ,m_sector_vector->at(sector_number-1).az_start,
                               m_sector_vector->at(sector_number-1).az_end))) {
        qDebug() << "unlock";
        m_plan_storage->unloock();
        return 255;
    }

    for(uint16_t i = 0;  i < cel_plan->m; ++i) {
        int16_t a[2] = {cel_plan->cel[i][0], cel_plan->cel[i][1]};
        uint8_t current_sector_number = calculate_sector(a, *m_sector_vector);
        //Если изменился сектор приема в плане, либо обрабатывется последние целеукозание, то
        //валидируется  полученный отрезок плана и добавляется в планы сектора и планы каналов данных.
        if(current_sector_number != sector_number) {
            if(current_sector_number == 0) {
                if(m_data_plans->find(cel_plan->chanel_number) != m_data_plans->end()){
                    if(m_data_plans->at(cel_plan->chanel_number).is_empty()) {
                        m_data_plans->extract(cel_plan->chanel_number);
                    }
                }
              //  if(m_sector_plans->at(sector_number).is_empty()){
              //      m_sector_plans->extract(sector_number);
              //  }
                m_plan_storage->unloock();
                return 255;
            }
            else {
                if((current_sector_number > 1) && (current_sector_number < 5)) {
                    qInfo() <<  "Сектор" << current_sector_number<<"не доступен.";
                    if(m_data_plans->find(cel_plan->chanel_number)!= m_data_plans->end()){
                        if(m_data_plans->at(cel_plan->chanel_number).is_empty()) {
                            m_data_plans->extract(cel_plan->chanel_number);
                        }
                    }
                    m_plan_storage->unloock();
                    return current_sector_number
                                                   ;
                }
            }


            if(segment_ptr->time_cel->time.size() == 1) {
                    QDateTime time = segment_ptr->time_cel->time.front();
                    qint16 az =segment_ptr->time_cel->az.front();
                    qint16 angle = segment_ptr->time_cel->angle.front();
                    segment_ptr->time_cel->time.push_back(time.addMSecs(segment_ptr->msec_delta));
                    segment_ptr->time_cel->az.push_back(az);
                    segment_ptr->time_cel->angle.push_back(angle);
            }

            std::optional<std::list<std::shared_ptr<SegmentPlan>>> toDelete =
                (*m_data_plans)[cel_plan->chanel_number].validateSegment(segment_ptr);

            if(toDelete.has_value()) {
                if(first_assign)
                    dataToDelete.emplace(toDelete->begin(), toDelete->end());
                else
                    dataToDelete->insert(dataToDelete->end(),toDelete->begin(), toDelete->end());
                first_assign = false;
            }

            bool sector_status =
                (*m_sector_plans)[sector_number].validateSegment(segment_ptr, dataToDelete);
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
                segment_ptr->initCel(cel_plan, current_sector_number,cel_plan->chanel_number, i,
                                    m_sector_vector->at(current_sector_number-1).az_start,
                                     m_sector_vector->at(current_sector_number-1).az_end);
                sector_number = current_sector_number;
            }
            else {
                if(m_data_plans->find(cel_plan->chanel_number) != m_data_plans->end()){
                    if(m_data_plans->at(cel_plan->chanel_number).is_empty()){
                        m_data_plans->extract(cel_plan->chanel_number);
                    }
                }
                m_plan_storage->unloock();
                qDebug() << "unlock";
                return sector_number;
            }
        }

        segment_ptr->appendCel(cel_plan);

        if(i == lastCelIndex) {
            std::optional<std::list<std::shared_ptr<SegmentPlan>>> toDelete =
                (*m_data_plans)[cel_plan->chanel_number].validateSegment(segment_ptr);
            if(toDelete.has_value()) {
                if(first_assign)
                    dataToDelete.emplace(toDelete->begin(), toDelete->end());
                else
                    dataToDelete->insert(dataToDelete->end(),toDelete->begin(), toDelete->end());
                first_assign = false;

                //qDebug() << "To delete size" << dataToDelete->size();
            }

            bool sector_status =
                (*m_sector_plans)[sector_number].validateSegment(segment_ptr, dataToDelete);

            if (sector_status) {
                segment_ptr->sector_number = sector_number;
                segment_ptr->data_chanel_number = cel_plan->chanel_number;

                PlanToAppend plan;
                plan.seg = segment_ptr;
                plan.sector_number = sector_number;
                plan.chanel_number = cel_plan->chanel_number;
                plansToAppend.push_back(plan);

                if (dataToDelete.has_value()) {
                    std::set<long long> cell_id_to_delete;
                    std::for_each(dataToDelete->begin(),dataToDelete->end(),
                                  [&cell_id_to_delete](std::shared_ptr<SegmentPlan>plan) {
                        cell_id_to_delete.insert(plan->id);
                    });

                    auto data_plan_segments = m_data_plans->at(cel_plan->chanel_number).segments();
                    std::for_each(data_plan_segments.begin(), data_plan_segments.end(),
                                  [&dataToDelete, &cell_id_to_delete](std::shared_ptr<SegmentPlan> plan) {
                        auto it =  cell_id_to_delete.find(plan->id);
                        if(it != cell_id_to_delete.end()) {
                            dataToDelete->push_back(plan);
                        }
                    });

                    std::for_each(dataToDelete->begin(), dataToDelete->end(),
                                  [this](std::shared_ptr<SegmentPlan> plan) {
                        (*m_sector_plans)[plan->sector_number].remove(plan);
                        qDebug() << "Chanel number" << plan->data_chanel_number;
                        (*m_data_plans)[plan->data_chanel_number].remove(plan);
                        if((*m_sector_plans)[plan->sector_number].is_empty()) {
                            m_sector_plans->extract(plan->sector_number);
                            qDebug() << "Планы сектора" << plan->sector_number << "выполнены.";
                        }
                        emit stopSegment(plan->data_chanel_number, plan->chanel_number, plan->sector_number);
                    });
                }
                auto plans_to_append_it = plansToAppend.begin();
                while(plans_to_append_it != plansToAppend.end()) {
                    (*m_sector_plans)[plans_to_append_it->sector_number].append(plans_to_append_it->seg);
                    (*m_data_plans)[plans_to_append_it->chanel_number].append(plans_to_append_it->seg);
                    ++plans_to_append_it;
                }
            }
            else {
                if(m_data_plans->find(cel_plan->chanel_number)!= m_data_plans->end()){
                    if(m_data_plans->at(cel_plan->chanel_number).is_empty()) {
                        m_data_plans->extract(cel_plan->chanel_number);
                    }
                }
                m_plan_storage->unloock();
                qDebug() << "unlock";
                return sector_number;
            }
        }
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

void PlanFactory::onPlanRecieved(std::shared_ptr<Cel> cel, long long packet_id)
{ 	if (!p2_connected){
        qDebug() << "Соеденение с П2 не установленно";
        emit messageHandled(packet_id, 255);
    }
    else {
        int ret = createPlan(cel);
        if(ret == 0) {
            qInfo() << "Планы созданы";
            emit messageHandled(packet_id, 0);
        }
        else {
            if(ret == 255) {
                qInfo() << "Неверные входны данные";
            }
            else {
                qInfo() << "Невозможно создать план слеженеия. Планы пересекаются в сеторе" <<  ret;
            }
            emit messageHandled(packet_id, ret);
        }
    }
}

void PlanFactory::onP2SocketStateChanging(bool p2_con)
{
    qDebug() << "State change " << p2_con;
    p2_connected = p2_con;
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

double PlanFactory::getTime() const
{
    auto now = QDateTime::currentDateTime();
    double OADate2 = (now.toMSecsSinceEpoch() /86400000.0) + 25569.0;

    return OADate2;
}

bool PlanFactory::check_data(std::shared_ptr<Cel> cel) const
{
    if((cel->chanel_number < 0) || (cel->chanel_number > 12)) {
        qInfo() << "Неверно задан канал данных";
        return false;
    }

    if((cel->polarization < 0) || (cel->polarization > 6)) {
        qInfo() << "Неверно задана поляризация";
        return false;
    }

    // if((cel->frequency < 1544000) || (cel->frequency > 1545000)) {
    //     qInfo() << "Неверно задана частота"
    //     return false;
    // }
    double current_time = getTime();
    if ((cel->start_time >  (current_time + 1.0)) ||
        (cel->end_time > (current_time+ 1.0)) ||
        (cel->start_time > cel->end_time)
        ) {
        qInfo() << "Начало и конец отрезка плана не должны превышать суток";
        return false;
    }

    return true;
}
