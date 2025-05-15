#include "logmessage.h"

LogMessage::LogMessage(const QtMsgType type, const QString &message, const QString &file, const QString &function, const int line) :
    type{type}, message{message}, file{file}, function{function}, line{line}
{
    timestamp = QDateTime::currentDateTime();
    threadId = QThread::currentThreadId();
}

QString LogMessage::toString(const QString &msgFormat, const QString &timestampFormat) const
{
    QString decorated=msgFormat+"\n";
    decorated.replace("{msg}",message);

    if (decorated.contains("{timestamp}"))
    {
        decorated.replace("{timestamp}",timestamp.toString(timestampFormat));
    }

    QString typeNr;
    typeNr.setNum(type);
    decorated.replace("{typeNr}",typeNr);

    switch (type)
    {
    case QtDebugMsg:
        decorated.replace("{type}","DEBUG   ");
        break;
    case QtWarningMsg:
        decorated.replace("{type}","WARNING ");
        break;
    case QtCriticalMsg:
        decorated.replace("{type}","CRITICAL");
        break;
    case QtFatalMsg: // or QtSystemMsg which has the same int value
        decorated.replace("{type}","FATAL   ");
        break;
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    case QtInfoMsg:
        decorated.replace("{type}","INFO    ");
        break;
#endif
    }

    decorated.replace("{file}",file);
    decorated.replace("{function}",function);
    decorated.replace("{line}",QString::number(line));

    QString threadId = QString("0x%1").arg(qulonglong(QThread::currentThreadId()), 8, 16, QLatin1Char('0'));
    decorated.replace("{thread}",threadId);

    return decorated;
}

QtMsgType LogMessage::getType() const
{
    return type;
}
