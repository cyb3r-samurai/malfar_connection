#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>
#include "messagehandler.h"
#include "Message.h"
#include "simpletabledata.h"
#include "celmodel.h"

class MessageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit MessageProcessor (QObject *parent = nullptr,
                               SimpleTableData *model = nullptr,
                               CelModel *celmodel = nullptr);

public slots:
    void device_data_ready(Packet);
    void set_request(Request_Type);
    void set_cel(Cel);

signals:
    void message_ready(QByteArray, QByteArray);
private:
    SimpleTableData* model;
    QList<MessageHandler *> handlers_;
    CelModel* m_celmodel;
};

#endif // MESSAGEPROCESSOR_H
