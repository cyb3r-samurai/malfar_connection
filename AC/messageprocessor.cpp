#include "messageprocessor.h"

MessageProcessor::MessageProcessor(PlanStorage* p_s, ReportStateChecker* r_s, AC* ac, QObject *parent)
    : QObject{parent}, m_state_checker{r_s}, m_plan_storage{p_s}, m_ac{ac}
{
    m_packet_storage = new QVector<Packet>;

    my_timer = new QTimer();
    my_timer->start(2000);
    connect(my_timer, &QTimer::timeout, this, &MessageProcessor::keep_alive);
    connect(my_timer, &QTimer::timeout, r_s, &ReportStateChecker::onTimer);

    m_msg_handlers = new QList<std::shared_ptr<MessageHandler>>;

    auto m_cel_handler_ptr = std::make_shared<CelHandler>();
    connect(m_cel_handler_ptr.get(), &CelHandler::celCreated, m_ac, &AC::OnCelRecieved);
    m_msg_handlers->append(m_cel_handler_ptr);

    auto  stop_handler_ptr = std::make_shared<StopHandler>();
    connect(stop_handler_ptr.get(), &StopHandler::stopRecieve, m_ac, &AC::onStopRecieve);
    m_msg_handlers->append(stop_handler_ptr);

    auto session_request_ptr = std::make_shared<SessionRequestHandler>();
    connect(session_request_ptr.get(), &SessionRequestHandler::requestRecieved,
            m_state_checker, &ReportStateChecker::onRequest);

    m_msg_handlers->append(session_request_ptr);

    connect(r_s, &ReportStateChecker::reciveStateCreated, this, &MessageProcessor::onReciveStateCreated);
    connect(r_s, &ReportStateChecker::sessionInfoCreated, this, &MessageProcessor::onSessionStateCreated);
    connect(r_s, &ReportStateChecker::acStateCreated, this, &MessageProcessor::onAcStateCreated);
    connect(ac, &AC::messageHandled, this, &MessageProcessor::statusResponse);

    auto &broker = MessageBroker::get();
    connect(&broker, &MessageBroker::MessagePublished, this, &MessageProcessor::handlePacket);
    connect(&broker, &MessageBroker::MessagePublished, this, &MessageProcessor::savePacket);
}

void MessageProcessor::on_client_msg_recieved(Header header, QByteArray msg_data)
{
    auto &provider = SequentialIdProvider::get();
    long long id = provider.next();
    Packet packet(header, msg_data, id);

    auto &broker = MessageBroker::get();
    broker.publish(packet);
    //qDebug() << QThread::currentThreadId();
}

void MessageProcessor::keep_alive()
{
    m_plan_storage->lockRead();
    m_test_data = m_plan_storage->sector_plans();
    m_plan_storage->unloock();
    //print_current_state();
}

void MessageProcessor::handlePacket(Packet &packet)
{
    for (qsizetype i = 0; i < m_msg_handlers->size(); ++i) {
        if(m_msg_handlers->at(i)->handleMessage(packet)) {
        }
    }
}

void MessageProcessor::savePacket(Packet &packet)
{
    m_packet_storage->push_back(packet);
}

void MessageProcessor::on_connected()
{
    m_connected = true;
}

void MessageProcessor::onReciveStateCreated(std::shared_ptr<RecieveState> r_s)
{

    //qDebug() << "Recive state recieved in MessageProcessor";
   // qDebug() << "Number of segments in ReciveState";
    //qDebug() << r_s->n;
    for(int i = 0; i < r_s->n; ++i) {
        //qDebug() << "segment data";
        //qDebug() << r_s->chanel_mas[i].real_chanel_number<< r_s->chanel_mas[i].ka_number
        //         <<r_s->chanel_mas[i].signal_level;
    }
    if (m_connected) {
         Header header;
         header.msg_type  = 0x81;
         header.n = No_alignmet_size::recieve_state + r_s->n * No_alignmet_size::chanel_info;
         emit message_created(header, r_s->serializeStruct());
    }
}

void MessageProcessor::onSessionStateCreated(std::shared_ptr<SessionInfo> s_i)
{
    qDebug() << "Session ready to be send";
}

void MessageProcessor::onAcStateCreated(std::shared_ptr<AcState> a_s)
{
    qDebug() << "AcState ready to be send";
}

void MessageProcessor::statusResponse(long long id, quint8 status)
{
  //  qDebug() << "Messgae ID: " << id << " Status " << status;
    double time;
    quint8 msg_type;
    auto it = m_packet_storage->begin();
    while(it != m_packet_storage->end()) {
        if(it->id == id) {
            time = it->header.time;
            msg_type = it->header.msg_type;
            break;
        }
        ++it;
    }
    if (it == m_packet_storage->end()) {
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
