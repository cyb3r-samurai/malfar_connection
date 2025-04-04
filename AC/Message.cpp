#include "Message.h"
#include <QDebug>

inline QDataStream &operator <<(QDataStream &stream, SubSessionInfo &sI){
    stream << sI.a << sI.b << sI.c << sI.d <<  sI.strart_time << sI.end_time
           << sI.first_c[0] << sI.first_c[1] << sI.last_c[0] << sI.last_c[1];
    return stream;
}

RecieveState::RecieveState(quint8 n_)
    : n(n_)
{
    sector_mas = new SectorInfo[n];
}

QByteArray RecieveState::serializeStruct()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << n;
    for (quint8 i = 0; i < n; i++) {
        stream << sector_mas[i];
    }

    return data;
}

SessionsInfo::SessionsInfo(quint8 n)
    : n{n}
{
    session_mas = new SubSessionInfo[n];
}

QByteArray SessionsInfo::serializeStruct()
{
    QByteArray data;
    QDataStream  stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << n;
    for (qint8 i = 0; i < n; i++) {
        stream << session_mas[i];
    }
    return data;
}

inline QDataStream &operator<< (QDataStream &stream, SessionInfo &sI) {
    stream << sI.a << sI.b << sI.c << sI.d[0] << sI.d[1];
    return stream;
}

inline QDataStream &operator <<(QDataStream &stream, SectorInfo &sI) {
    stream << sI.a << sI.b << sI.c << sI.m;
   for (qint8 i = 0; i < sI.m; i++) {
        stream << sI.session_mas[i];
    }
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

    stream << session_id << state << number << time << offset << az[0] << az[1];
    stream << m;

    for(quint16 i = 0; i < m; i++) {
        stream << info[i][0];
        stream << info[i][1];
    }
    return data;
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
    stream >> cel.number >> cel.sesssion_number >> cel.polarization
        >> cel.frequency >> cel.time >> cel.step >> cel.m;
    cel.cel = new qint16*[cel.m];
    for (quint16 i = 0; i < cel.m; i++) {
        cel.cel[i] = new qint16[2];
    }
    for (quint16 i = 0; i < cel.m; i++) {
        for(qsizetype j = 0; j < 2; j++) {
            stream >> cel.cel[i][j];        }
    }
    return stream;
};
