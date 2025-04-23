#ifndef SESSIONFACTORY_H
#define SESSIONFACTORY_H

#include <memory>
#include <session.h>
#include "Message.h"

class SessionFactory
{
public:
    SessionFactory();
    std::unique_ptr<Session> CreateSession(Cel&&);
};

#endif // SESSIONFACTORY_H
