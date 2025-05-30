#include "messageprocessor.h"

MessageProcessor::MessageProcessor(PlanStorage* p_s, ReportStateChecker* r_s, AC* ac, QObject *parent)
    : QObject{parent}, m_state_checker{r_s}, m_plan_storage{p_s}, m_ac{ac}
{
    initMessageBroker();
    initHandlers();
    initResponceMessageCreation();
    initPacketStorage();
    startTimer();
}

void MessageProcessor::on_client_msg_recieved(const Header& header, const QByteArray& msg_data)
{
    auto &provider = SequentialIdProvider::get();
    long long id = provider.next();
    Packet packet(header, msg_data, id);

    auto &broker = MessageBroker::get();
    broker.publish(packet);
}

void MessageProcessor::handlePacket(const Packet &packet)
{
    for (qsizetype i = 0; i < m_msg_handlers->size(); ++i) {
        if (m_msg_handlers->at(i)->handleMessage(packet)) {

        }
    }
}

void MessageProcessor::savePacket(const Packet &packet)
{
    m_packet_storage->push_back(packet);
}

void MessageProcessor::on_connected()
{
    m_connected = true;

    QTimer::singleShot(1000, [this](){ emit timeToCreateStartMessage(); });
}

void MessageProcessor::onReciveStateCreated(std::shared_ptr<RecieveState> r_s)
{
    if (m_connected) {
         Header header;
         header.msg_type  = 0x81;
         header.n = No_alignmet_size::recieve_state + r_s->n * No_alignmet_size::chanel_info;
         QByteArray bytes = r_s->serializeStruct();
         emit message_created(header, bytes);
    }
}

void MessageProcessor::onSessionStateCreated(std::shared_ptr<SessionInfo> s_i)
{
    qDebug() << "Session ready to be send";
    if(m_connected) {
        Header header;
        header.msg_type = 0x84;
        header.n = 1 + 2* s_i->active_data_chanel_count;
        for(int i =0; i < s_i->active_data_chanel_count; ++i){
            header.n += s_i->m_chanel_data[i].segment_count * 27;
            for(int j = 0; j < s_i->m_chanel_data[i].segment_count; ++j) {
                header.n += s_i->m_chanel_data[i].segment_plan[j].m * 4;
            }
        }
        QByteArray bytes = s_i->SerializeStruct();
        qDebug() << bytes.size();
        qDebug() << header.n;

        Q_ASSERT(bytes.size() == header.n);
        emit message_created(header, bytes);
    }
}

void MessageProcessor::onAcStateCreated(std::shared_ptr<AcState> a_s)
{
    qDebug() << "AcState ready to be send";
    if(m_connected) {
        Header header;
        header.msg_type = 0x83;
        header.n = 7168 + 640 + 60 + 6;

        AcState acState;
        QByteArray data = acState.serializeStruct();
        qDebug() <<  data.size();
        qDebug() << header.n;

        Q_ASSERT(data.size() == header.n);
        emit message_created(header , data);
    }
}

void MessageProcessor::statusResponse(long long id, quint8 status)
{
  //  qDebug() << "Messgae ID: " << id << " Status " << status;
    double time;
    quint8 msg_type;
    auto it = m_packet_storage->begin();
    bool found = false;
    while(it != m_packet_storage->end()) {
        if(it->id == id) {
            time = it->header.time;
            msg_type = it->header.msg_type;
            m_packet_storage->erase(it);
            found = true;
            break;
        }
        ++it;
    }
    if (!found) {
        qWarning() << "Missing id";
        return;
    }

    Status s(time, msg_type, status);
    Header header;
    header.msg_type = 0x80;
    header.n = No_alignmet_size::status;

    emit message_created(header, s.SerialiazeStruct());
}

quint32 MessageProcessor::seconds_since_epoch()
{
    QDateTime now = QDateTime::currentDateTime();

    QDateTime epoch(QDate(2000, 1, 1), QTime(0, 0, 0), Qt::UTC);
    qint64 time =  now.toSecsSinceEpoch();
    qint64 epoch_time = epoch.toSecsSinceEpoch();
    return time - epoch_time;
}
QDateTime MessageProcessor::secondsToDatetime(quint32 seconds) const
{
    QDateTime epoch(QDate(2000, 1, 1), QTime(0, 0, 0), Qt::UTC);
    return epoch.addSecs(seconds);
}

void MessageProcessor::print_current_state() const
{
    qDebug() << "current AC state :";
    qDebug() << "initiated sector count" << m_test_data->size();
    for(size_t i = 1; i <= m_test_data->size(); ++i) {
        qDebug() << "Sector number: " << i;
        (*m_test_data)[i].display_info();
    }
}

void MessageProcessor::initHandlers()
{
    m_msg_handlers = new QList<std::shared_ptr<MessageHandler>>;

    auto m_cel_handler_ptr = std::make_shared<CelHandler>();
    connect(m_cel_handler_ptr.get(), &CelHandler::celCreated, m_ac->plan_factory(), &PlanFactory::onPlanRecieved);
    m_msg_handlers->append(m_cel_handler_ptr);

    auto  stop_handler_ptr = std::make_shared<StopHandler>();
    connect(stop_handler_ptr.get(), &StopHandler::stopRecieve, m_ac, &AC::onStopRecieve);
    m_msg_handlers->append(stop_handler_ptr);

    auto session_request_ptr = std::make_shared<SessionRequestHandler>();
    connect(session_request_ptr.get(), &SessionRequestHandler::requestRecieved,
            m_state_checker, &ReportStateChecker::onRequest);
    m_msg_handlers->append(session_request_ptr);

    auto ac_state_request_ptr = std::make_shared<AcStateHandler>();
    connect(ac_state_request_ptr.get(), &AcStateHandler::requestCreated,
            m_state_checker, &ReportStateChecker::onAcStateRequest);
    m_msg_handlers->append(ac_state_request_ptr);
}

void MessageProcessor::initResponceMessageCreation()
{
    connect(m_state_checker, &ReportStateChecker::reciveStateCreated, this, &MessageProcessor::onReciveStateCreated);
    connect(m_state_checker, &ReportStateChecker::sessionInfoCreated, this, &MessageProcessor::onSessionStateCreated);
    connect(m_state_checker, &ReportStateChecker::acStateCreated, this, &MessageProcessor::onAcStateCreated);
    connect(m_ac, &AC::messageHandled, this, &MessageProcessor::statusResponse);
    connect(m_ac->plan_factory(), &PlanFactory::messageHandled, this, &MessageProcessor::statusResponse);
}

void MessageProcessor::initMessageBroker()
{
    auto &broker = MessageBroker::get();
    connect(&broker, &MessageBroker::MessagePublished, this, &MessageProcessor::handlePacket);
    connect(&broker, &MessageBroker::MessagePublished, this, &MessageProcessor::savePacket);
}

void MessageProcessor::initPacketStorage()
{
    m_packet_storage = new QVector<Packet>;
}

void MessageProcessor::startTimer()
{
    my_timer = new QTimer();
    my_timer->start(2000);
    connect(my_timer, &QTimer::timeout, m_state_checker, &ReportStateChecker::onTimer);
    connect(this, &MessageProcessor::timeToCreateStartMessage, m_state_checker, &ReportStateChecker::onStartingServer);

}
