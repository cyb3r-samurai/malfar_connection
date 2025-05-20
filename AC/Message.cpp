#include "Message.h"
#include <QDebug>


RecieveState::RecieveState()
{

}

RecieveState::RecieveState(quint8 n_)
    : n(n_)
{
    chanel_mas = new ChanelInfo[n];
}

void RecieveState::initializeChanelMas(quint8 n)
{
    chanel_mas = new ChanelInfo[n];

}

QByteArray RecieveState::serializeStruct()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << n;
    for (quint8 i = 0; i < n; i++) {
        stream << chanel_mas[i];
    }

    return data;
}

inline QDataStream &operator<< (QDataStream &stream, ChanelInfo &ch_i) {
    stream << ch_i.freq << ch_i.ka_number << ch_i.vec[0] << ch_i.vec[1]
           << ch_i.real_chanel_number << ch_i.pol << ch_i.signal_level
           << ch_i.sector_number << ch_i.sector_state << ch_i.sector_start
           << ch_i.sector_end;
    return stream;
}

Report::Report(quint16 m)
    : m{m}
{
    info  = new qint8*[m];
    for (quint16 i = 0; i < m; i++) {
        info[i] = new qint8[2];
    }
    for (quint16 i = 0; i < m; i++) {
        for (qsizetype j = 0; j < 2; j++)
            info[i][j] = 1;
    }

}

QByteArray Report::serializeStruct()
{
    QByteArray data;
    QDataStream stream (&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << chanel_number << ac_state << ka_number << time <<
        az[0] << az[1];
    stream << m;

    for(quint16 i = 0; i < m; i++) {
        stream << info[i][0];
        stream << info[i][1];
    }
    return data;
}

AcState::AcState()
{
    cdo_state = new CDO_state[sector_count];
}

QByteArray AcState::serializeStruct()
{
    QByteArray data;
    QDataStream stream (&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << state_ac << state_sch << comm_state << comm_state2;

    return data;
}

QDataStream &operator>>(QDataStream &stream, Cel &cel) {
    stream >> cel.chanel_number >> cel.polarization >> cel.ka_number
           >> cel.frequency >> cel.start_time >> cel.end_time >> cel.m;
    cel.cel = new qint16*[cel.m];
    for (quint16 i = 0; i < cel.m; i++) {
        cel.cel[i] = new qint16[2];
    }
    for (quint16 i = 0; i < cel.m; i++) {
        for(qsizetype j = 0; j < 2; j++) {
            stream >> cel.cel[i][j];
        }
    }
    return stream;
}

inline QDataStream &operator<< (QDataStream &stream, Emmiter_state& Em_s ) {
    stream << Em_s.pol << Em_s.state << Em_s.signal_level;
    return stream;
}

inline QDataStream &operator<< (QDataStream &stream, CAM_state& cam_state)  {
    stream << cam_state.cam_state << cam_state.amperage <<cam_state.temperature
           <<cam_state.emmiter_count;

    for(int i = 0; i < cam_state.emmiter_count; ++i) {
        stream << cam_state.emm_state[i];
    }
    return stream;
}

inline QDataStream &operator<< (QDataStream &stream, CDO_state& cdo_state)
{
    stream << cdo_state.state << cdo_state.amperage
           << cdo_state.voltage << cdo_state.temperature
           << cdo_state.cdo_state << cdo_state.cam_count;
    for (int i = 0; i < cdo_state.cam_count; ++i) {
        stream << cdo_state.cam_info[i];
    }
        return stream;
}


Status::Status(double time_, quint8 msg_type_, quint8 status_)
    : time{time_}, msg_type{msg_type_}, status{status_}
{

}

QByteArray Status::SerialiazeStruct()
{
    QByteArray data;
    QDataStream stream (&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << time << msg_type << status;

    return data;
}

QByteArray SessionInfo::SerializeStruct()
{
    QByteArray data;
    QDataStream stream (&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << active_data_chanel_count << m_chanel_data;

    return data;
}

inline QDataStream &operator<< (QDataStream &stream, ChanelData& ch_data) {
    stream << ch_data.chanel_number << ch_data.segment_count << ch_data.segment_plan;

    return stream;
}


inline QDataStream &operator<< (QDataStream &stream, MessageSegmentPlan& m_seg_plan) {
    stream << m_seg_plan.sector_number << m_seg_plan.chanel_number << m_seg_plan.pol
           << m_seg_plan.ka_number << m_seg_plan.start_time << m_seg_plan.end_time
           << m_seg_plan.m;

    for( int i = 0; i < m_seg_plan.m; ++i) {
        stream << m_seg_plan.cel[i][0] << m_seg_plan.cel[i][1];
    }

    return stream;
}

CAM_state::CAM_state()
{
    emm_state = new Emmiter_state[emmiter_count];
}

CDO_state::CDO_state()
{
    cam_info = new CAM_state[cam_count];
}

Cel::~Cel()
{
    for (uint16_t i = 0; i < m; ++i) {
        delete[] cel[i];
    }
    delete[] cel;
}
