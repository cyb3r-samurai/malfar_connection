#include "logger.h"

QString Logger::msgFormat;
QString Logger::timestampFormat;

Logger::Logger(const QString &msgFormat, const QString &timestampFormat, QObject *parent) :
    QObject{parent}
{
    Logger::msgFormat = msgFormat;
    Logger::timestampFormat = timestampFormat;
}

void Logger::msgHandler(const QtMsgType type, const QMessageLogContext &context, const QString& message)
{
    LogMessage* logMessage = new LogMessage(type, message, context.file, context.function, context.line);
    fputs(qPrintable(logMessage->toString(msgFormat,timestampFormat)),stderr);
    fflush(stderr);
}

void Logger::installMsgHandler()
{
    qInstallMessageHandler(msgHandler);

}

Logger::~Logger()
{
    qInstallMessageHandler(nullptr);
}
