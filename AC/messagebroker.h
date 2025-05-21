#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include <packet.h>

#include <QObject>


class MessageBroker : public QObject
{
    Q_OBJECT
public:
    static MessageBroker& get() {
        static MessageBroker broker;
        return broker;
    };

    template <typename T>
    void subscribe(QObject* handler,void(T::* slot)(const Packet &)){
        connect(this, &MessageBroker::MessagePublished, handler, slot);
    }

    void publish(const Packet& packet) {
        emit MessagePublished(packet);
    }

signals:
    void MessagePublished(const Packet& packet);

private:
    MessageBroker() = default;
};

#endif // MESSAGEBROKER_H
