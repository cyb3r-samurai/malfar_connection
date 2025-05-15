#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <QDateTime>
#include <QtGlobal>
#include <QThread>

class LogMessage
{
public:
    LogMessage(const QtMsgType type, const QString &message,
               const QString &file, const QString & function,
               const int line);

    QString toString(const QString& msgFormat, const QString& timestampFormat) const;
    QtMsgType getType() const;

private:
    QDateTime timestamp;
    QtMsgType type;
    Qt::HANDLE threadId;
    QString message;
    QString file;
    QString function;
    int line;
};

#endif // LOGMESSAGE_H
