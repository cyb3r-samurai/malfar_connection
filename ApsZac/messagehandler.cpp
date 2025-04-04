#include "messagehandler.h"

MessageHandler::MessageHandler() {}

RecieveStateHandler::RecieveStateHandler(QList<QPair<Header, RecieveState> > *storage)
    : recieve_state_storage_{storage}
{}

RecieveState RecieveStateHandler::deserialize_recieve_state(QByteArray &data)
{
    RecieveState r_s;
    QDataStream stream(&data, QDataStream::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream >> r_s;
    return r_s;
}

bool RecieveStateHandler::HandleMessage( Packet &packet) {
    if (packet.header.msg_type != 0x81) {
        return false;
    }
    RecieveState  rs  = deserialize_recieve_state(packet.data);
    qDebug() << "Secotor info recieved";
    recieve_state_storage_->append(QPair<Header, RecieveState>(packet.header, rs));
    return true;
}


SessionsInfoHandler::SessionsInfoHandler(QList<QPair<Header, SessionsInfo> > *storage, SimpleTableData *model)
    : sessions_info_storage_{storage}, model{model}
{}

bool SessionsInfoHandler::HandleMessage (Packet &packet)
{
    if (packet.header.msg_type != 0x82) {
        return false;
    }
    SessionsInfo si = deserialize_sessions_info(packet.data);
    qDebug() << "Sessions info recieved";
    sessions_info_storage_->append(QPair<Header, SessionsInfo> (packet.header, si));
    QList<SubSessionInfo> new_values;
    for (quint8 i = 0; i < si.n; i++) {
        new_values.append(si.session_mas[i]);
    }
    model->append(&new_values);
    return true;

}

SessionsInfo SessionsInfoHandler::deserialize_sessions_info(QByteArray &data)
{
    SessionsInfo s_i;
    QDataStream stream(&data, QDataStream::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> s_i;
    return s_i;
}

ReportHandler::ReportHandler(QList<QPair<Header, Report> > *storage, CelModel *celmodel)
    : report_info_storage_{storage}, m_celmodel{celmodel}
{

}

bool ReportHandler::HandleMessage(Packet &packet)
{

    if (packet.header.msg_type != 0x83) {
        return false;
    }
    Report report = deserialize_report(packet.data);

    QVector<double> i_vec;
    i_vec.resize(report.m);
    QVector<double> q_vec;
    q_vec.resize(report.m);
    for(qsizetype i = 0; i < report.m; i++){
        i_vec[i] = report.info[i][0];
        q_vec[i] = report.info[i][1];
    }
    qDebug() << "Report message recieved" ;
    qDebug() << report.number;

    if(!m_celmodel->exist(report.number)) {
        m_celmodel->addKa(report.number);
        m_celmodel->updateData(report.number, i_vec, q_vec);
    } else {
        m_celmodel->updateData(report.number, i_vec, q_vec);
    }

   // report_info_storage_->append(QPair<Header, Report>(packet.header, report));
    return true;
}

Report ReportHandler::deserialize_report(QByteArray &data)
{
    Report report;
    QDataStream stream(&data, QDataStream::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream >> report;
    return report;
}

AcStateHandler::AcStateHandler(QList<QPair<Header, AcState> > *storage)
    :ac_state_storage_{storage}
{

}

bool AcStateHandler::HandleMessage(Packet &packet)
{
    if (packet.header.msg_type != 0x84) {
        return false;
    }
    AcState state = deserialize_ac_state(packet.data);
    qDebug() <<"AcState recieved";
    ac_state_storage_->append(QPair<Header, AcState>(packet.header, state));
    return true;

}

AcState AcStateHandler::deserialize_ac_state(QByteArray &data)
{
    AcState state;
    QDataStream stream (&data, QDataStream::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream >> state;
    return state;
}
