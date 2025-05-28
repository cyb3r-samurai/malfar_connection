// Структуры сообщений

#ifndef MESSAGE_H
#define MESSAGE_H


#include <QVector>
#include <QIODevice>

#include <QFloat16>

namespace No_alignmet_size {
    const quint8 session_info = 8;
    const quint8 sector_info = 6;
    const quint8 recieve_state = 1;
    const quint8 subsession_info = 20;
    const quint8 sessions_info = 1;
    const quint8 report = 26;
    const quint8 as_state = 3;
    const quint8 status = 10;
    const quint8 chanel_info = 22;
};

class Requst_Message {
public:
    quint8 msg_type;
};

struct ChanelInfo{
public:
    quint32 freq;// Центральная чистотв в МГЦЖц
    quint16 ka_number;
    qint16 vec[2]; // Текущий азимут, угол места
    quint8 real_chanel_number; // номер физического канала приема(луча) в секторе приема.
    qint8 pol;
    float signal_level;
    quint8 sector_number;
    qint8 sector_state;
    qint16 sector_start; // Азимут начала сектора
    qint16 sector_end;   // Азиту конца сектора

    friend QDataStream &operator <<(QDataStream &stream, ChanelInfo &ch_i);
};

class RecieveState {
public:
    RecieveState();
    RecieveState(quint8 n_);
  //  RecieveState(std::map<int, DataChanel> &&);
    quint8 n;
    ChanelInfo * chanel_mas;

    void initializeChanelMas(quint8 n);
    QByteArray serializeStruct();
};


class Report {
public:
    Report(quint32 m);
    quint8 data_chanel_number = 13;
    quint8 ac_state = 3;
    quint16 ka_number = 5;
    double time = 4;
    qint16 az[2] = {1,2};
    quint32 m;
    qint8** info;

    QByteArray serializeStruct();
};

class Emmiter_state{
public:
    quint8 number = 1;
    quint8 pol = 1;
    quint8 state = 1;
    float signal_level = 1; //Среднеквадратический урдвень сигнала на входу АЦП

    friend QDataStream &operator << (QDataStream &stream, Emmiter_state &emmiter);
};

class CAM_state {
public:
    CAM_state();

    quint8 cam_state = 1;
    float amperage = 1;
    float temperature = 1;
    quint8 emmiter_count = 16;
    Emmiter_state* emm_state ;

    friend QDataStream &operator << (QDataStream &stream, CAM_state &emmiter);
};

class CDO_state {
public:

    CDO_state();
    quint8 state = 1;
    float amperage = 1;
    float voltage = 1;
    float temperature = 1;
    quint8 cdo_state = 1;
    quint8 cam_count = 16;
    CAM_state * cam_info;

    friend QDataStream &operator << (QDataStream &stream, CDO_state &cdo_state);
};


class AcState {
public:
    AcState();
    quint8 state_ac = 0;
    quint8 state_sch = 0;
    quint8 comm_state = 0;
    quint8 comm_state2 = 0;
    quint8 pc_state = 0;

    quint8 sector_count = 4;

    CDO_state* cdo_state;

    QByteArray serializeStruct();
};


class Cel {
public:

    ~Cel();
    long long id;
    quint8 chanel_number;
    qint8 polarization;
    quint16 ka_number;
    quint32 frequency;
    double start_time;
    double end_time;
    quint16 m;
    qint16 **cel;

    friend QDataStream &operator >> (QDataStream &stream, Cel &cel);
};
class Status {
public:
    Status(double time_, quint8 msg_type_, quint8 status_);
    double time;
    quint8 msg_type;
    quint8 status;

    QByteArray SerialiazeStruct();
};

struct MessageSegmentPlan {
    MessageSegmentPlan();
    void init(uint16_t m);
    uint8_t sector_number; // 1, 2, 3, 4
    uint8_t chanel_number; // номер физического канала приема
    uint8_t pol; // 1 - правая круговая
        // 2 - левая круговая
        // 3 - вертикальная
        // 4 - горизонтальная
        // 5 - линейная + 45 град
        // 6 - линейна - 45 град
    uint16_t ka_number;
    uint32_t freq;
    double start_time;
    double end_time;
    uint16_t m;
    int16_t** cel;

    friend QDataStream &operator << (QDataStream &stream, MessageSegmentPlan& msg_seg);
};

struct ChanelData {
    void init(uint8_t chanel_number);
    uint8_t chanel_number;
    uint8_t segment_count;
    MessageSegmentPlan* segment_plan;

    friend QDataStream &operator << (QDataStream &stream, ChanelData& ch_data);
};

class SessionInfo {
public:
    SessionInfo();
    SessionInfo(uint8_t n);
    void init(uint8_t n);
    uint8_t active_data_chanel_count;
    ChanelData * m_chanel_data;

    QByteArray SerializeStruct();
};
#endif // MESSAGE_H
