#include "messageprocessor.h"

MessageProcessor::MessageProcessor(QObject *parent, MessageStorage *message_storage_,
                                   SimpleTableData *model, CelModel *celmodel)
    : QObject{parent} ,model{model}, message_storage_{message_storage_}, m_celmodel{celmodel}
{
    handlers_.append(new RecieveStateHandler(&message_storage_->ResiveState_s));
    handlers_.append(new SessionsInfoHandler(&message_storage_->SessionsInfo_s, model));
    handlers_.append(new ReportHandler(&message_storage_->Report_s, m_celmodel));
    handlers_.append(new AcStateHandler(&message_storage_->AcState_s));
}

void MessageProcessor::device_data_ready(Packet packet)
{
    for (qsizetype i = 0; i < handlers_.size(); i++) {
        if(handlers_[i]->HandleMessage(packet)) {
        }
    }
}

void MessageProcessor::set_request(Request_Type r_t)
{
    Header header;
    Requst_Message msg;
    header.msg_type = 0x01;
    header.n = 1;

    QByteArray header_bytes;
    QByteArray message_bytes;

    switch (r_t) {
    case  Request_Type::sessions_info :
        msg.msg_type = 0x82;
        break;
    case Request_Type::recieve_state :
        msg.msg_type = 0x81;
        break;
    case Request_Type::as_stat:
        msg.msg_type = 0x84;
        break;
    }

    header_bytes = header.serializeStruct();

    QDataStream stream(&message_bytes, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << msg.msg_type;

    emit message_ready(header_bytes, message_bytes);
}

void MessageProcessor::set_cel(Cel cel)
{
    Header header;
    header.msg_type = 0x01;
    header.n = No_alignment_size::cel + 4 * cel.m;

    QByteArray header_bytes;
    QByteArray message_bytes;

    header_bytes = header.serializeStruct();
    qDebug() << cel.start_time;
    qDebug() << cel.end_time;
    QDataStream stream(&message_bytes, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << cel;
    qDebug() << "Message data size";
    qDebug() << message_bytes.size();

    emit message_ready(header_bytes, message_bytes);
}
