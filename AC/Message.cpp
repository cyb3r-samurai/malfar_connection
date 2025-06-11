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

RecieveState::~RecieveState()
{
    delete this->chanel_mas;
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
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

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

Report::Report(quint32 m)
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

Report::~Report()
{
   // qDebug() << "destructor called";
    for(int i =0; i < m; ++i) {
        delete[] info[i];
    }
        delete[] info;
}

QByteArray Report::serializeStruct() const
{
    QByteArray data;
    QDataStream stream (&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << data_chanel_number << ac_state << ka_number << time <<
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
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    stream << state_ac << state_sch << comm_state << comm_state2 << pc_state << sector_count;

    for(int i = 0; i < sector_count; i++) {
        stream << cdo_state[i];
    }
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
    stream << Em_s.number<< Em_s.pol << Em_s.state << Em_s.signal_level;
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

SessionInfo::SessionInfo()
{
    active_data_chanel_count = 0;
}

SessionInfo::~SessionInfo()
{
  //  qDebug() << "SessionInfo destructor called";
    if(active_data_chanel_count != 0) {
        delete[] m_chanel_data ;
    }
}

void SessionInfo::init(uint8_t n)
{
    m_chanel_data = new ChanelData[n];
}

QByteArray SessionInfo::SerializeStruct()
{
    QByteArray data;
    QDataStream stream (&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);

    stream << active_data_chanel_count;

    for(int i = 0; i < active_data_chanel_count; i++) {
        stream << m_chanel_data[i];
    }

    return data;
}

inline QDataStream &operator<< (QDataStream &stream, ChanelData& ch_data) {
    stream << ch_data.chanel_number << ch_data.segment_count;
    for(int i = 0; i < ch_data.segment_count; i++) {
        stream << *(ch_data.segment_plan[i]);
    }

    return stream;
}


inline QDataStream &operator<< (QDataStream &stream, MessageSegmentPlan& m_seg_plan) {
    stream << m_seg_plan.sector_number << m_seg_plan.chanel_number << m_seg_plan.pol
           << m_seg_plan.ka_number<< m_seg_plan.freq << m_seg_plan.start_time << m_seg_plan.end_time
           << m_seg_plan.m;

   // qDebug() << "serialize cell";
    for( int i = 0; i < m_seg_plan.m; ++i) {
        stream << m_seg_plan.cel[i][0] << m_seg_plan.cel[i][1];

    //    qDebug() << m_seg_plan.cel[i][0] << m_seg_plan.cel[i][1];
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

MessageSegmentPlan::MessageSegmentPlan()
{

}

MessageSegmentPlan::~MessageSegmentPlan()
{
    //qDebug() << "segmentPlan deleted";
    for (int i = 0; i < m; ++i) {
        delete[] this->cel[i];
    }
    delete[] cel;
}

void MessageSegmentPlan::init(uint16_t m)
{
    cel = new int16_t *[m];
    for (size_t i = 0; i < m; ++i) {
        cel[i] = new int16_t[2];
    }
}

ChanelData::~ChanelData()
{
    //qDebug() << "Chanel data Deleted";

    for (int i= 0; i < segment_count; ++i){

        delete  segment_plan[i];
    }
    delete[] segment_plan;
}

void ChanelData::init(uint8_t chanel_number)
{
   // segment_plan = new MessageSegmentPlan[chanel_number];
}
