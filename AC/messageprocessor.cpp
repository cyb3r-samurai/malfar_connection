#include "messageprocessor.h"

MessageProcessor::MessageProcessor(PlanStorage* p_s, QObject *parent)
    : QObject{parent}, m_plan_storage{p_s}
{
    my_timer = new QTimer();
    my_timer->start(2000);

    connect(my_timer, &QTimer::timeout, this, &MessageProcessor::keep_alive);
}

void MessageProcessor::on_client_msg_recieved(Header header, QByteArray msg_data)
{
    //qDebug() << QThread::currentThreadId();
    if(header.msg_type == 0x02) {
        Requst_Message r_m;
        QDataStream stream(&msg_data, QIODevice::ReadOnly);
        stream.setByteOrder(QDataStream::LittleEndian);
        stream >> r_m.msg_type;
        qDebug() << "Request msg recieved";
        create_responce(r_m.msg_type);
    }
    else
    {
        if (header.msg_type == 0x01) {
            QDataStream stream(&msg_data, QIODevice::ReadOnly);
            stream.setByteOrder(QDataStream::LittleEndian);
            Cel cel;
            stream >> cel;
            qDebug() << "Cel recieved";
            qDebug() << cel.chanel_number;
            emit cel_recieved(std::make_shared<Cel>(std::move(cel)));
        }
    }
}

void MessageProcessor::keep_alive()
{
    m_plan_storage->lockRead();
    m_test_data = m_plan_storage->sector_plans();
    m_plan_storage->unloock();
    print_current_state();
}

void MessageProcessor::create_responce(quint8 type)
{
    // switch (type) {
    // case 0x81: {
    //     Header header;
    //     header.msg_type = 0x81;
    //     RecieveState r_s(1);
    //     r_s.sector_mas[0].session_mas = new SessionInfo[2];
    //     r_s.sector_mas[0].m = 2;
    //     r_s.sector_mas[0].session_mas[0].a = 33;

    //     header.n = No_alignmet_size::session_info * 2 + No_alignmet_size::sector_info
    //                + No_alignmet_size::recieve_state;
    //     QByteArray msg_bytes = r_s.serializeStruct();
    //     emit message_created(header, msg_bytes);
    // }
    //     break;
    // case 0x82: {
    //     Header header;
    //     header.msg_type = 0x82;
    //     SessionsInfo s_i(2);
    //     s_i.session_mas[0].a = 0;
    //     s_i.session_mas[1].a = 1;
    //     s_i.session_mas[0].b = 23;
    //     s_i.session_mas[1].b = 53;

    //     s_i.session_mas[0].strart_time = seconds_since_epoch();
    //     s_i.session_mas[0].end_time = seconds_since_epoch() + 15;
    //     s_i.session_mas[1].strart_time = seconds_since_epoch();
    //     s_i.session_mas[1].end_time = seconds_since_epoch() + 20;

    //     float a = 1.72;
    //     uint32_t b = (uint32_t)(*(uint32_t*)&a);

    //     s_i.session_mas[0].d = b;
    //     s_i.session_mas[1].d = b;

    //     header.n = No_alignmet_size::subsession_info*2 + No_alignmet_size::sessions_info;
    //     QByteArray msg_bytes = s_i.serializeStruct();
    //     emit message_created(header, msg_bytes);
    // }
    //     break;
    // case 0x84: {
    //     Header header;
    //     header.msg_type = 0x84;
    //     AcState state;

    //     header.n = No_alignmet_size::as_state;
    //     QByteArray msg_bytes = state.serializeStruct();
    //     emit message_created(header, msg_bytes);
    // }
    //     break;
    // default:
    //     break;
    // }
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
