#ifndef MESSAGE_H
#define MESSAGE_H

#include <QtTypes>
#include <QVector>
#include <QIODevice>

namespace No_alignmet_size {
    const quint8 session_info = 8;
    const quint8 sector_info = 6;
    const quint8 recieve_state = 1;
    const quint8 subsession_info = 20;
    const quint8 sessions_info = 1;
    const quint8 report = 16;
    const quint8 as_state = 3;
};

class Requst_Message {
public:
    quint8 msg_type;
};

struct SessionInfo{
public:
    quint8 a = 1;
    quint8 b = 2;
    quint16 c = 3;
    quint16 d[2] = {1,2};

    friend QDataStream &operator<< (QDataStream &stream, SessionInfo &sC);
};

struct SectorInfo{
public:
    qint16 a = 1;
    qint16 b = 2;
    qint8 c = 4;
    quint8 m = 4;
    SessionInfo* session_mas;

    friend QDataStream &operator <<(QDataStream &stream, SectorInfo &sC);
};

class RecieveState {
public:
    RecieveState(quint8 n_);
    quint8 n;
    SectorInfo * sector_mas;

    QByteArray serializeStruct();
};

class SubSessionInfo {
public:
    quint16 a = 114;
    qint8 b = 2;
    qint8 c = 2;
    quint32 d = 23;
    quint32 strart_time = 1;
    quint32 end_time = 23;
    qint16 first_c[2] = {1, 2};
    qint16 last_c[2] = {1, 4};

    friend QDataStream &operator <<(QDataStream &stream, SubSessionInfo &sC);
};

class SessionsInfo {
public:
    SessionsInfo(quint8 n);

    quint8 n;
    SubSessionInfo* session_mas;

    QByteArray serializeStruct();
};

class Report {
public:
    Report(quint16 m);
    quint8 session_id = 13;
    quint8 state = 3;
    quint16 number = 5;
    quint32 time = 4;
    quint16 offset = 4;
    qint16 az[2] = {1,2};
    quint16 m;
    qint8** info;

    QByteArray serializeStruct();
};

class AcState {
public:
    qint8 state_ac = 12;
    qint8 state_sch = 42;
    qint8 comm_state = 4;
    qint8 comm_state2 = 5;

    QByteArray serializeStruct();
};
class Cel {
public:
    quint16 number;
    qint8 sesssion_number;
    qint8 polarization;
    quint32 frequency;
    quint32 time;
    quint16 step;
    quint16 m;
    qint16 **cel;

    friend QDataStream &operator >> (QDataStream &stream, Cel &cel);
};
#endif // MESSAGE_H
