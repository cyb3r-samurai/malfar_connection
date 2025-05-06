#include "Message.h"

QDataStream &operator  >>(QDataStream &stream, SessionInfo &sI) {
    stream >> sI.a >> sI.b >> sI.c >> sI.d[0] >> sI.d[1];
    return stream;
}

QDataStream &operator >>(QDataStream &stream, SectorInfo &sI) {
    stream >> sI.a >> sI.b >> sI.c >> sI.m;
    sI.session_mas = new SessionInfo[sI.m];
    for (qint8 i = 0; i < sI.m; i++) {
        stream >> sI.session_mas[i];
    }
    return stream;
}
QDataStream &operator>> (QDataStream &stream, RecieveState &sC) {
    stream >> sC.n;
    sC.sector_mas = new SectorInfo[sC.n];
    for(quint8 i = 0; i < sC.n; i++) {
        stream >> sC.sector_mas[i];
    }
    return stream;
}

QDataStream &operator>> (QDataStream &stream, SessionsInfo &sI) {
    stream >> sI.n;
    sI.session_mas = new SubSessionInfo[sI.n];
    for(quint8 i = 0; i < sI.n; i++) {
        stream >> sI.session_mas[i];
    }
    return stream;
}

QDataStream &operator >> (QDataStream &stream, SubSessionInfo &sC) {
    stream >> sC.a >> sC.b >> sC.c >> sC.d >> sC.start_time >> sC.end_time
        >> sC.first_c[0] >> sC.first_c[1] >> sC.last_c[0] >> sC.last_c[1];
    return stream;
}

QDataStream &operator >> (QDataStream &stream, AcState &state){
    stream >> state.state_ac >> state.state_sch >> state.comm_state >> state.comm_state2;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Report &report){
    stream >> report.session_id >> report.state >> report.number >> report.time
        >> report.ofset >> report.az[0] >> report.az[1] >> report.m;
    report.info = new qint8*[report.m];

    for(quint16 i = 0; i < report.m; i++) {
        report.info[i] = new qint8[2];
    }
    for(quint16 i = 0; i < report.m; i++) {
        for(qsizetype j = 0; j < 2; j++) {
            stream >> report.info[i][j];
        }
    }
    return stream ;
}

QDataStream &operator << (QDataStream &stream, Cel &cel) {
    stream << cel.chanel_number << cel.polarization << cel.ka_number
           << cel.frequency << cel.start_time << cel.end_time << cel.m;
    for(quint16 i = 0; i < cel.m; i++) {
        for(qsizetype j = 0; j < 2; j++) {
            stream << cel.cel[i][j];
        }
    }
    return stream;
}

Status::Status()
{

}
