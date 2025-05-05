#ifndef MESSAGE_H
#define MESSAGE_H

//#include <QtTypes>
#include <QVector>
#include <QIODevice>

#include "packet.h"


class CelData{
public:
    int kaNumber;
    QVector<double> iData;
    QVector<double> qData;
};

namespace No_alignment_size {
    const quint8 cel = 26;
};
enum class Request_Type
{
    recieve_state,
    sessions_info,
    as_stat
};


class Requst_Message {
public:
    quint8 msg_type;
};

class Session_Message {
public:
    quint16 CA_number;
    qint8 session_number;
    qint8 polarization;
    quint32 frequency;
    quint32 time;
    quint16 step;
    quint16 m;
    qint16 **info;
};


class SessionInfo {
public:
    quint8 a;
    quint8 b;
    quint16 c;
    quint16 d[2];

    friend QDataStream &operator>> (QDataStream &stream, SessionInfo &sC);
    };

class SectorInfo {
public:
    qint16 a;
    qint16 b;
    qint8 c;
    quint8 m;
    SessionInfo* session_mas;

    friend QDataStream &operator>> (QDataStream &stream, SectorInfo &sC);
};

class RecieveState {
public:
    quint8 n;
    SectorInfo * sector_mas;

    friend QDataStream &operator>> (QDataStream &stream, RecieveState &sC);
};

class SubSessionInfo {
public:
    quint16 a;
    qint8 b ;
    qint8 c ;
    quint32 d ;
    quint32 start_time ;
    quint32 end_time ;
    qint16 first_c[2] ;
    qint16 last_c[2] ;

    friend QDataStream &operator >> (QDataStream &stream, SubSessionInfo &sC);
};
class SessionsInfo {
public:
    quint8 n;
    SubSessionInfo* session_mas;

    friend QDataStream &operator>> (QDataStream &stream, SessionsInfo &sC);
};

class Report {
public:
    quint8 session_id;
    quint8 state;
    quint16 number;
    quint32 time;
    quint16 ofset;
    qint16 az[2];
    quint16 m;
    qint8** info;

    friend QDataStream &operator>> (QDataStream &stream, Report &sC);
};

class AcState {
public:
    qint8 state_ac;
    qint8 state_sch;
    qint8 comm_state;
    qint8 comm_state2;

    friend QDataStream &operator>> (QDataStream &stream, AcState &sC);
};


class Cel {
public:
    quint8 chanel_number;
    qint8 polarization;
    quint16 ka_number;
    quint32 frequency;
    double start_time;
    double end_time;
    quint16 m;
    qint16 **cel;

    friend QDataStream &operator << (QDataStream &stream, Cel &cel);
};
#endif // MESSAGE_H
