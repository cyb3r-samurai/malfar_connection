#ifndef LOGGER_H
#define LOGGER_H

#include "logmessage.h"

#include <QObject>


class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(const QString& msgFormat = "{timestamp} {type}: {msg}",
                    const QString& timestampForamt = "dd.MM.yyyy hh::mm::ss.zzz",
                    QObject *parent = nullptr);

    void installMsgHandler();
    ~Logger();

    static void msgHandler(const QtMsgType, const QMessageLogContext &context,
                    const QString& messgae);

private:
    static QString msgFormat;
    static QString timestampFormat;
};

#endif // LOGGER_H
